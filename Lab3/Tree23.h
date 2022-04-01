#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using std::cout;
using std::endl;

namespace Lab3
{
	#define WrongKeyEx "Wrong key" 
	#define IterNotInstalledEx "Iterator is not installed"

	template <class K, class V>
	class Tree23
	{
		class Node;
		class Leaf;
		class Internal;

	public:
		
		class Iterator
		{
		public:
			Iterator() {};
			Iterator(Tree23& tree, Internal* leafParent, Leaf* leaf)
			{  this->tree = &tree; current = leaf; curParent = leafParent; }
			V& operator *() const
			{
				if (current != nullptr)
					return current->value;

				throw IterNotInstalledEx;
			}
			bool operator++(int value) //переход к следующему узлу при прямом обходе
			{ 
				tree->GetNext(&curParent, &current);  return current != nullptr;
			}
			bool operator--(int value)  //переход к предыдущему узлу при прямом обходе
			{
				tree->GetPrev(&curParent, &current);  return current != nullptr;
			}
			bool operator == (Iterator iter) const { return tree == iter.tree && current == iter.current; }
			bool operator != (Iterator iter) const { return !(*this == iter); }
		protected:
			Tree23* tree = nullptr; 
			Internal* curParent = nullptr;
			Leaf* current = nullptr;

			friend class Tree23;
		};

		class ReverseIterator
		{
		public:
			ReverseIterator() {};
			ReverseIterator(Tree23& tree, Internal* leafParent, Leaf* leaf)
			{ this->tree = &tree; current = leaf; curParent = leafParent; }
			V& operator *() const
			{
				if (current != nullptr)
					return current->value;

				throw IterNotInstalledEx;
			}
			bool operator++(int value) //переход к предыдущему узлу при прямом обходе
			{ 
				tree->GetPrev(&curParent, &current);  return current != nullptr;
			}
			bool operator--(int value) // переход к следующему узлу при прямом обходе
			{ 
				tree->GetNext(&curParent, &current);  return current != nullptr;
			}
			bool operator == (ReverseIterator iter) const { return tree == iter.tree && current == iter.current; }
			bool operator != (ReverseIterator iter) const { return !(*this == iter); }
		protected:
			Tree23* tree = nullptr;
			Internal* curParent = nullptr;
			Leaf* current = nullptr;

			friend class Tree23;
		};

		Tree23() {};
		Tree23(const Tree23<K, V>& tree);
		~Tree23() { Clear(); }
		int GetSize() const { return size; }
		void Clear();
		bool IsEmpty() const { return size == 0; }
		V& operator[] (K key); 
		bool Add(K key, V value);
		bool Remove(K key);
		int GetReadElementsCount() const { return readElements; } 
		void Print() const;

		Iterator Begin();
		Iterator End() { return Iterator(*this, nullptr, nullptr); } 
		ReverseIterator Rbegin();
		ReverseIterator Rend() { return ReverseIterator(*this, nullptr, nullptr); } 
	protected:
		int size = 0;
		mutable int readElements = 0; //число узлов дерева, просмотренных предыдущей операцией
		Node* root = nullptr;

		enum class BypassMode { AddToTree, DeleteFromMemory }; //режим обхода дерева
		void BypassTree(Node* root, BypassMode mode); //обход дерева, где для каждого узла выполняется действие согласно режиму обхода

		void PrintLevels(Node* root, int level) const; //рекурсивный вывод дерева
		bool FindNodeByKey(Internal* curRoot, Internal** parent, int* sonId, K key) const;
		bool Remove(Internal* curRoot, K key);
		void GetPrev(Internal** parent, Leaf** leaf) const; //следующий узел при прямом обходе
		void GetNext(Internal** parent, Leaf** leaf) const; //предыдущий узел при прямом обходе
		bool Insert(Internal* curRoot, Internal* curRootParent, Leaf* leaf);
		void Split(Internal* nodeToSplit, Internal* parent, int sonId);
		void Merge(Internal* nodeToMerge, Internal* parent, int sonId);
		
		class Node
		{
		public:
			Node() {};
			virtual void Print() const = 0;
		};

		class Leaf : public Node
		{
		public:
			K key;
			V value;
			Leaf(K key, V value) : key(key), value(value) {}
			void Print() const { std::cout << key; }
		};

		class Internal : public Node
		{
		public:
			static const int maxSonsCount = 3;
			static const int minSonsCount = 2;
			std::vector<Node*> sons;
			K minKeys[2];
			K min;

			void Print() const
			{ 
				std::cout << "[" << minKeys[0] << ",";
				if (sons.size() == 3)
					std::cout << minKeys[1];
				else
					std::cout << "-";
				std::cout << "]";
			}
			bool AreSonsLeafs() const { return dynamic_cast<Leaf*>(sons[0]); }
			bool SortSons() 
			{ 
				if (AreSonsLeafs() == false)
					return false;

				std::sort(sons.begin(), sons.end(), [](Node* node1, Node* node2)
				{
					return static_cast<Leaf*>(node1)->key < static_cast<Leaf*>(node2)->key;
				}
				);
				return true;
			}
			void SetMinKeys()
			{
				if (AreSonsLeafs())
				{
					min = static_cast<Leaf*>(sons[0])->key;
					minKeys[0] = static_cast<Leaf*>(sons[1])->key;
					if (sons.size() == 3)
						minKeys[1] = static_cast<Leaf*>(sons[2])->key;
				}
				else
				{
					min = static_cast<Internal*>(sons[0])->min;
					minKeys[0] = static_cast<Internal*>(sons[1])->min;
					if (sons.size() == 3)
						minKeys[1] = static_cast<Internal*>(sons[2])->min;
				}
			}
			int GetSonIdWithKey(K key)
			{
				if (AreSonsLeafs() == false)
					return -1;

				for (int i = 0; i < sons.size(); i++)
				{
					if (static_cast<Leaf*>(sons[i])->key == key)
						return i;
				}

				return -1;
			}
			int GetSonIdForNewNode(K key) const
			{
				if (key < minKeys[0]) return 0;
				else if (key == minKeys[0]) return -1;
				else
				{
					if (sons.size() == 2) return 1;

					if (key < minKeys[1]) return 1;
					else if (key == minKeys[1]) return -1;
					else return 2;
				}
			}
			int GetSonIdToFindNode(K key) const
			{
				if (key < minKeys[0]) return 0;
				else if (key == minKeys[0]) return 1;
				else
				{
					if (sons.size() == 2) return 1;

					if (key < minKeys[1]) return 1;
					else if (key == minKeys[1]) return 2;
					else return 2;
				}
			}
		};

		friend class Iterator;
		friend class ReverseIterator;
		
	};

	//открытые методы дерева

	template<class K, class V>
	inline Tree23<K, V>::Tree23(const Tree23<K, V>& tree)
	{
		BypassTree(tree.root, BypassMode::AddToTree);
	}

	template<class K, class V>
	inline void Tree23<K, V>::Clear()
	{
		size = 0;
		BypassTree(this->root, BypassMode::DeleteFromMemory);
		root = nullptr;
	}

	template<class K, class V>
	inline V& Tree23<K, V>::operator[](K key)
	{
		if (IsEmpty())
			throw WrongKeyEx;

		if (dynamic_cast<Leaf*>(root))
		{
			Leaf* rootLeaf = static_cast<Leaf*>(root);
			if (rootLeaf->key == key)
				return rootLeaf->value;
			throw WrongKeyEx;
		}

		Internal* parent = nullptr;
		int sonId;
		if (FindNodeByKey(static_cast<Internal*>(root), &parent, &sonId, key))
		{
			return static_cast<Leaf*>(parent->sons[sonId])->value;
		}

		throw WrongKeyEx;
	}

	template<class K, class V>
	inline bool Tree23<K, V>::Add(K key, V value)
	{
		readElements = 0;	
		Leaf* newNode = new Leaf(key, value);

		if (IsEmpty()) //если корень единственный элемент, он - лист
		{
			root = newNode;
			size++;
			return true;
		}

		//если добавляем второй элемент,то пробуем объединить корень и новый узел под новым внутр. узлом
		if (dynamic_cast<Leaf*>(this->root)) 
		{
			Leaf* oldRoot = static_cast<Leaf*>(root);

			if (oldRoot->key == newNode->key)
			{
				delete newNode;
				return false;
			}

			Internal* newRoot = new Internal();

			newRoot->sons.push_back(oldRoot);
			newRoot->sons.push_back(newNode);
			newRoot->SortSons();
			newRoot->SetMinKeys();


			root = newRoot;
			size++;
			readElements++;
			return true;
		}

		Internal* internalRoot = static_cast<Internal*>(root);
		
		if (Insert(internalRoot, nullptr, newNode))
		{
			if (internalRoot->sons.size() > Internal::maxSonsCount)
			{
				Split(internalRoot, nullptr, 0);
				internalRoot->SetMinKeys();
			}
			static_cast<Internal*>(root)->SetMinKeys();
			return true;
		}

		delete newNode;
		return false;
	}

	template<class K, class V>
	inline bool Tree23<K, V>::Remove(K key)
	{
		if (dynamic_cast<Leaf*>(root))
		{
			if (static_cast<Leaf*>(root)->key == key)
			{
				delete root;
				root = nullptr;
				size--;
				return true;
			}
			return false;
		}

		Internal* internalRoot = static_cast<Internal*>(root);

		if (Remove(internalRoot, key))
		{
			if (internalRoot->sons.size() < Internal::minSonsCount)
			{
				Merge(internalRoot, nullptr, 0);
				return true;
			}
			else if (internalRoot->sons.size() > Internal::maxSonsCount)
			{
				Split(internalRoot, nullptr, 0);
				internalRoot->SetMinKeys();
			}
			static_cast<Internal*>(root)->SetMinKeys();
			return true;
		}
		return false;
	}

	template<class K, class V>
	inline void Tree23<K, V>::Print() const
	{
		if (IsEmpty())
		{
			std::cout << "Tree is empty" << std::endl;
			return;
		}

		PrintLevels(root, 0);
	}

	template<class K, class V>
	inline  typename Tree23<K, V>::Iterator Tree23<K, V>::Begin()
	{
		Leaf* leaf = nullptr;
		Internal* parent = nullptr;
		if (IsEmpty()) {}
		else if (dynamic_cast<Leaf*>(root))
			leaf = static_cast<Leaf*>(root);
		else
		{		
			Internal* rootInternal = static_cast<Internal*>(root);

			int sonId;
			if (FindNodeByKey(rootInternal, &parent, &sonId, rootInternal->min))
			{
				if (parent == nullptr)
					leaf = static_cast<Leaf*>(rootInternal->sons[sonId]);
				else
					leaf = static_cast<Leaf*>(parent->sons[sonId]);
			}		
		}
		return Iterator(*this, parent, leaf);
	}

	template<class K, class V>
	inline typename Tree23<K, V>::ReverseIterator Tree23<K, V>::Rbegin()
	{
		Leaf* leaf = nullptr;
		Internal* parent = nullptr;

		if (IsEmpty()) { return Rend(); }
		else if (dynamic_cast<Leaf*>(root))
		{
			leaf = static_cast<Leaf*>(root);
			return ReverseIterator(*this, parent, leaf);
		}

		Internal* curRoot = static_cast<Internal*>(root);

		while (curRoot->AreSonsLeafs() == false)
		{
			curRoot = static_cast<Internal*>(curRoot->sons.back());
		}

		parent = curRoot;
		leaf = static_cast<Leaf*>(curRoot->sons.back());

		return ReverseIterator(*this, parent, leaf);
	}

	//приватные методы дерева

	template<class K, class V>
	inline bool Tree23<K, V>::Insert(Internal* curRoot, Internal* curRootParent, Leaf* node)
	{
		readElements++;

		if (curRoot->AreSonsLeafs())
		{
			if (curRoot->GetSonIdWithKey(node->key) >= 0)
				return false;

			curRoot->sons.push_back(node);
			if (curRoot->sons.size() <= Internal::maxSonsCount)
			{
				curRoot->SortSons();
				curRoot->SetMinKeys();
			}

			size++;
			return true;
		}

		Internal* nodeToInsert = nullptr;

		int sonId;
		if ((sonId = curRoot->GetSonIdForNewNode(node->key)) < 0)
			return false;

		nodeToInsert = static_cast<Internal*>(curRoot->sons[sonId]);

		if (Insert(nodeToInsert, curRoot, node) == false)
			return false;

		if (nodeToInsert->sons.size() > Internal::maxSonsCount)
		{
			Split(nodeToInsert, curRoot, sonId);
		}

		curRoot->SetMinKeys();

		return true;
	}

	template<class K, class V>
	inline void Tree23<K, V>::Split(Internal* nodeToSplit, Internal* parent, int sonId)
	{
		Internal* second = new Internal();

		if (nodeToSplit->AreSonsLeafs())
		{
			nodeToSplit->SortSons();
		}

		for (int i = 0; i < 2; i++)
		{
			second->sons.insert(second->sons.begin(), nodeToSplit->sons.back());
			nodeToSplit->sons.pop_back();
		}

		nodeToSplit->SetMinKeys();
		second->SetMinKeys();

		if (parent == nullptr)
		{
			parent = new Internal();
			this->root = parent;
			parent->sons.insert(parent->sons.begin(), nodeToSplit);
		}

		parent->sons.insert(parent->sons.begin() + sonId + 1, second);  //вставляем новый узел справа от разделяемого
	}

	template<class K, class V>
	inline void Tree23<K, V>::Merge(Internal* nodeToMerge, Internal* parent, int sonId)
	{
		Node* onlySon = *(nodeToMerge->sons.begin());

		if (parent == nullptr)
		{
			root = static_cast<Leaf*>(onlySon);
			return;
		}

		int sonIdToMerge = (sonId == parent->sons.size() - 1 ? sonId - 1 : sonId + 1);
		Internal* sonToMerge = static_cast<Internal*>(parent->sons[sonIdToMerge]);
		sonToMerge->sons.push_back(onlySon);

		if (sonToMerge->sons.size() > Internal::maxSonsCount)
			Split(sonToMerge, parent, sonIdToMerge);

		parent->sons.erase(parent->sons.begin() + sonId);
		delete nodeToMerge;
	}

	template<class K, class V>
	inline void Tree23<K, V>::BypassTree(Node* root, BypassMode mode)
	{
		if (root == nullptr)
			return;

		Node* node = root;
		std::stack<Node*> _stack;
		_stack.push(node);

		while (_stack.empty() == false)
		{
			node = _stack.top();
			_stack.pop();

			if (dynamic_cast<Internal*>(node))
			{
				Internal* internalNode = static_cast<Internal*>(node);

				for (int i = 0; i < internalNode->sons.size(); i++)
					_stack.push(internalNode->sons[i]);

				if (mode == BypassMode::DeleteFromMemory)
					delete internalNode;

				continue;
			}
			
			if (mode == BypassMode::DeleteFromMemory)
				delete node;
			else if (mode == BypassMode::AddToTree)
			{
				Leaf* leaf = static_cast<Leaf*>(node);
				Add(leaf->key, leaf->value);
			}
		}
	}

	template<class K, class V>
	inline bool Tree23<K, V>::FindNodeByKey(Internal* curRoot, Internal** parent, int* sonId, K key) const
	{
		if (curRoot->AreSonsLeafs())
		{
			int id = curRoot->GetSonIdWithKey(key);
			if (id >= 0)
			{
				*parent = curRoot;
				*sonId = id;
				return true;
			}
			return false;
		}

		int id;

		if ((id = curRoot->GetSonIdToFindNode(key)) < 0)
			return false;

		return FindNodeByKey(static_cast<Internal*>(curRoot->sons[id]), parent, sonId, key);
	}

	template<class K, class V>
	inline bool Tree23<K, V>::Remove(Internal* curRoot, K key)
	{
		readElements++;

		if (curRoot->AreSonsLeafs())
		{
			int nodeId = curRoot->GetSonIdWithKey(key);
			if (nodeId < 0)
				return false;

			delete curRoot->sons[nodeId];
			curRoot->sons.erase(curRoot->sons.begin() + nodeId);

			if (curRoot->sons.size() >= Internal::minSonsCount)
			{
				curRoot->SetMinKeys();
			}

			size--;
			return true;
		}

		Internal* nodeToInsert = nullptr;

		int sonId = curRoot->GetSonIdToFindNode(key);

		nodeToInsert = static_cast<Internal*>(curRoot->sons[sonId]);

		if (Remove(nodeToInsert, key) == false)
			return false;

		if (nodeToInsert->sons.size() < Internal::minSonsCount)
		{
			Merge(nodeToInsert, curRoot, sonId);
		}
		else if (nodeToInsert->sons.size() > Internal::maxSonsCount)
		{
			Split(nodeToInsert, curRoot, sonId);
		}
		else
			curRoot->SetMinKeys();

		return true;
	}

	template<class K, class V>
	inline typename void Tree23<K, V>::GetNext(Internal** parent, Leaf** leaf) const
	{
		if (*parent == nullptr) //нет родителя -> узел - корень и единственный элемент дерева
		{
			*parent = nullptr;
			*leaf = nullptr;
			return;
		}

		Internal* _parent = *parent;
		Leaf* _leaf = *leaf;

		int sonId = _parent->GetSonIdToFindNode(_leaf->key);
		if (sonId != _parent->sons.size() - 1) //если узел не последний сын своего родителя, возвращаем следующего сына
		{
			*leaf = static_cast<Leaf*>(_parent->sons[++sonId]);
			return;
		}
		//иначе - если внутр. узел - единственный в дереве - нет следующего
		if (_parent == static_cast<Internal*>(root))
		{
			*parent = nullptr;
			*leaf = nullptr;
			return;
		}

		//иначе - ищем последнего родителя, в котором parent - не самый правый сын
		Internal* curRoot = static_cast<Internal*>(root);
		Internal* lastSuccessRoot = nullptr;
		int lastSuccessId;
		K keyToFind = _leaf->key;
		while (curRoot->AreSonsLeafs() == false)
		{
			int id = curRoot->GetSonIdToFindNode(keyToFind);

			if (id != curRoot->sons.size() - 1)
			{
				lastSuccessId = id;
				lastSuccessRoot = curRoot;
			}

			curRoot = static_cast<Internal*>(curRoot->sons[id]);
		}

		if (lastSuccessRoot == nullptr)
		{
			*parent = nullptr;
			*leaf = nullptr;
			return;
		}

		Internal* rightInternal = static_cast<Internal*>(lastSuccessRoot->sons[lastSuccessId + 1]);

		//находим внутр. узел, в котором содержится следующий Leaf( c мин. ключом rightInternal)
		FindNodeByKey(rightInternal, parent, &sonId, rightInternal->min);

		*leaf = static_cast<Leaf*>((*parent)->sons[sonId]);
	}

	template<class K, class V>
	inline typename void Tree23<K, V>::GetPrev(Internal** parent, Leaf** leaf) const
	{
		if (*parent == nullptr) //нет родителя -> узел - корень и единственный элемент дерева
		{
			*parent = nullptr;
			*leaf = nullptr;
			return;
		}

		Internal* _parent = *parent;
		Leaf* _leaf = *leaf;

		int sonId = _parent->GetSonIdToFindNode(_leaf->key);
		if (sonId > 0) //если узел не первый сын своего родителя, возвращаем предыдущего сына
		{
			*leaf = static_cast<Leaf*>(_parent->sons[--sonId]);
			return;
		}

		//иначе - проверка на равенство узла и мин. элемента всего дерева
		if (_parent->min == static_cast<Internal*>(root)->min)
		{
			*parent = nullptr;
			*leaf = nullptr;
			return;
		}

		//внутр. узел левее текущего, если в нём происходит поиск узла с ключом, меньше мин. у текущего
		Internal* curRoot = static_cast<Internal*>(root);
		K keyToFind = _parent->min - 1;
		while (curRoot->AreSonsLeafs() == false)
		{
			int id = curRoot->GetSonIdToFindNode(keyToFind);
			curRoot = static_cast<Internal*>(curRoot->sons[id]);
		}
		*parent = curRoot;
		*leaf = static_cast<Leaf*>(curRoot->sons.back());
	}

	template<class K, class V>
	inline void Tree23<K, V>::PrintLevels(Node* root, int level) const
	{
		int levelOffset = 6;
		if (dynamic_cast<Internal*>(root))
		{
			Internal* internal = static_cast<Internal*>(root);

			if (internal->sons.size() == 3)
				PrintLevels(internal->sons[2], level + 1);

			PrintLevels(internal->sons[1], level + 1);

			for (int i = 0; i <= levelOffset * level; i++)
			{
				printf(" ");
			}

			root->Print();
			cout << std::endl;

			PrintLevels(internal->sons.front(), level + 1);
			return;
		}

		for (int i = 0; i <= levelOffset * level; i++)
		{
			printf(" ");
		}

		root->Print(); 
		cout << std::endl;
	}

}