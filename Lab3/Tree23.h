#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <iostream>

using std::cout;
using std::endl;

namespace Lab3
{
	#define WrongKeyEx "Wrong key" 
	#define IterOutOfRangeEx "Iterator out of range"

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

				throw IterOutOfRangeEx;
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

				throw IterOutOfRangeEx;
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
		Tree23(const Tree23<K, V>& tree) { BypassTree(tree.root, BypassMode::AddToTree); };
		~Tree23() { Clear(); }
		int GetSize() const { return size; }
		void Clear();
		bool IsEmpty() const { return size == 0; }
		V Get(K key) const { return GetValue(key); };
		void Set(K key, V newValue) { GetValue(key) = newValue; }
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

		V& GetValue(K key) const;
		void PrintLevels(Node* root, int level) const; //рекурсивный вывод дерева
		bool FindNodeByKey(Internal* curRoot, Internal** parent, int* sonId, K key) const;
		bool Insert(Internal* curRoot, Internal* curRootParent, Leaf* leaf);
		bool Remove(Internal* curRoot, K key);
		bool TrySplitOrMerge(Internal* node, Internal* parent);
		void Split(Internal* nodeToSplit, Internal* parent);
		void Merge(Internal* nodeToMerge, Internal* parent);
		void GetPrev(Internal** parent, Leaf** leaf) const; //следующий узел при прямом обходе
		void GetNext(Internal** parent, Leaf** leaf) const; //предыдущий узел при прямом обходе
		
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
			int GetSonIdToFindNode(K key) const
			{
				if (AreSonsLeafs())
				{
					for (int i = 0; i < sons.size(); i++)
					{
						if (static_cast<Leaf*>(sons[i])->key == key)
							return i;
					}
					return -1;
				}

				if (key < minKeys[0]) return 0;
				if (key == minKeys[0]) return 1;
				if (sons.size() == 2 || key < minKeys[1]) return 1;
				if (key >= minKeys[1]) return 2;
			}
			bool ContainsInMinKeys(K key) const
			{
				return (key == minKeys[0] || (sons.size() == 3 && key == minKeys[1]));
			}
			int Find(Node* node) const { return std::distance(sons.begin(), find(sons.begin(), sons.end(), node)); }
		};

		friend class Iterator;
		friend class ReverseIterator;
		
	};

	//открытые методы дерева

	template<class K, class V>
	inline void Tree23<K, V>::Clear()
	{
		size = 0;
		BypassTree(this->root, BypassMode::DeleteFromMemory);
		root = nullptr;
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
			TrySplitOrMerge(internalRoot, nullptr);
			static_cast<Internal*>(root)->SetMinKeys();
			return true;
		}

		delete newNode;
		return false;
	}

	template<class K, class V>
	inline bool Tree23<K, V>::Remove(K key)
	{
		readElements = 0;
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
		if (Remove(internalRoot, key) == false)
			return false;

		TrySplitOrMerge(internalRoot, nullptr);
		static_cast<Internal*>(root)->SetMinKeys();
		return true;
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
		if (IsEmpty()) { return End(); }
		if (size == 1) { return Iterator(*this, nullptr, static_cast<Leaf*>(root)); }

		Leaf* leaf = nullptr;
		Internal* parent = static_cast<Internal*>(root);

		while (parent->AreSonsLeafs() == false)
		{
			parent = static_cast<Internal*>(parent->sons.front()); //спуск по самому левому сыну
		}

		leaf = static_cast<Leaf*>(parent->sons.front()); //самый левый лист
		return Iterator(*this, parent, leaf);
	}

	template<class K, class V>
	inline typename Tree23<K, V>::ReverseIterator Tree23<K, V>::Rbegin()
	{
		if (IsEmpty()) { return Rend(); }
		if (size == 1) { return ReverseIterator(*this, nullptr, static_cast<Leaf*>(root)); }

		Leaf* leaf = nullptr;
		Internal* parent = static_cast<Internal*>(root);

		while (parent->AreSonsLeafs() == false)
		{
			parent = static_cast<Internal*>(parent->sons.back()); //спуск по самому правому сыну
		}

		leaf = static_cast<Leaf*>(parent->sons.back()); //самый правый лист
		return ReverseIterator(*this, parent, leaf);
	}

	//приватные методы дерева

	template<class K, class V>
	inline V& Tree23<K, V>::GetValue(K key) const
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
	inline void Tree23<K, V>::PrintLevels(Node* root, int level) const
	{
		int levelOffset = 6;

		if (dynamic_cast<Internal*>(root))
		{
			Internal* internal = static_cast<Internal*>(root);

			for (int i = internal->sons.size() - 1; i >= 1; i--)
				PrintLevels(internal->sons[i], level + 1);

			cout << std::string(levelOffset * level, ' ');
			root->Print();
			cout << std::endl;

			PrintLevels(internal->sons.front(), level + 1);
			return;
		}

		cout << std::string(levelOffset * level, ' ');
		root->Print();
		cout << std::endl;
	}

	template<class K, class V>
	inline bool Tree23<K, V>::Insert(Internal* curRoot, Internal* curRootParent, Leaf* node)
	{
		readElements++;

		if (curRoot->AreSonsLeafs())
		{
			if (curRoot->GetSonIdToFindNode(node->key) >= 0)
				return false;

			curRoot->sons.push_back(node);
			curRoot->SortSons();
			curRoot->SetMinKeys();

			size++;
			return true;
		}

		if (curRoot->ContainsInMinKeys(node->key))
			return false;

		Internal* nodeToInsert = nullptr;

		int sonId;
		if ((sonId = curRoot->GetSonIdToFindNode(node->key)) < 0)
			return false;

		nodeToInsert = static_cast<Internal*>(curRoot->sons[sonId]);
		if (Insert(nodeToInsert, curRoot, node) == false)
			return false;

		TrySplitOrMerge(nodeToInsert, curRoot);
		curRoot->SetMinKeys();
		return true;
	}

	template<class K, class V>
	inline bool Tree23<K, V>::Remove(Internal* curRoot, K key)
	{
		readElements++;

		if (curRoot->AreSonsLeafs())
		{
			int nodeId = curRoot->GetSonIdToFindNode(key);
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

		if (TrySplitOrMerge(nodeToInsert, curRoot) == false)
			curRoot->SetMinKeys();

		return true;
	}

	template<class K, class V>
	inline bool Tree23<K, V>::TrySplitOrMerge(Internal* node, Internal* parent)
	{
		if (node->sons.size() < Internal::minSonsCount)
		{
			Merge(node, parent);
		}
		else if (node->sons.size() > Internal::maxSonsCount)
		{
			Split(node, parent);
		}
		else return false;
		return true;
	}

	template<class K, class V>
	inline void Tree23<K, V>::Split(Internal* nodeToSplit, Internal* parent)
	{
		Internal* second = new Internal();

		if (nodeToSplit->AreSonsLeafs())
		{
			nodeToSplit->SortSons();
		}

		//два последних сына разделяемого узла вставляем в начало второго узла
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

		//вставляем новый узел в вектор сыновей родителя справа от разделяемого
		parent->sons.insert(parent->sons.begin() + parent->Find(nodeToSplit) + 1, second);  
	}

	template<class K, class V>
	inline void Tree23<K, V>::Merge(Internal* nodeToMerge, Internal* parent)
	{
		Node* onlySon = *(nodeToMerge->sons.begin());

		if (parent == nullptr)
		{
			root = onlySon;
			return;
		}

		int sonId = parent->Find(nodeToMerge);
		bool mergeLeft = sonId == parent->sons.size() - 1;
		int sonIdToMerge = (mergeLeft ? sonId - 1 : sonId + 1); //если мы последний сын, объединяемся с предыдущим, иначе - со следующим
		Internal* sonToMerge = static_cast<Internal*>(parent->sons[sonIdToMerge]);

		//объединение с предыдущим -> сын вставляется в конец вектора сыновей sonToMerge, иначе - в начало 
		sonToMerge->sons.insert((mergeLeft ? sonToMerge->sons.end() : sonToMerge->sons.begin()), onlySon);

		parent->sons.erase(parent->sons.begin() + sonId);
		delete nodeToMerge;

		if (sonToMerge->sons.size() > Internal::maxSonsCount)
			Split(sonToMerge, parent);
		else
			sonToMerge->SetMinKeys();
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
			int id = curRoot->GetSonIdToFindNode(key);
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
	inline typename void Tree23<K, V>::GetNext(Internal** parent, Leaf** leaf) const
	{
		if (*parent == nullptr) //нет родителя -> узел - единственный элемент -> нет следующего 
		{
			*leaf = nullptr;
			return;
		}

		int sonId = (*parent)->GetSonIdToFindNode((*leaf)->key);
		if (sonId != (*parent)->sons.size() - 1) //если узел не последний сын своего родителя, возвращаем следующего сына
		{
			*leaf = static_cast<Leaf*>((*parent)->sons[++sonId]);
			return;
		}

		//иначе - ищем последнее место, где поиск нашего листа происходит не через последнего сына, т.е. корень соседнего (справа) поддерева
		Internal* curRoot = static_cast<Internal*>(root);
		Internal* rightNode = nullptr;
		while (curRoot->AreSonsLeafs() == false)
		{
			int id = curRoot->GetSonIdToFindNode((*leaf)->key);
			if (id != curRoot->sons.size() - 1)
			{
				rightNode = static_cast<Internal*>(curRoot->sons[id + 1]);
			}

			curRoot = static_cast<Internal*>(curRoot->sons[id]);
		}

		if (rightNode == nullptr)
		{
			*parent = nullptr;
			*leaf = nullptr;
			return;
		}

		while (rightNode->AreSonsLeafs() == false) //самый левый сын с листами
			rightNode = static_cast<Internal*>(rightNode->sons.front());
		
		*parent = rightNode;
		*leaf = static_cast<Leaf*>(rightNode->sons.front()); //самый левый лист
	}

	template<class K, class V>
	inline typename void Tree23<K, V>::GetPrev(Internal** parent, Leaf** leaf) const
	{
		if (*parent == nullptr) //нет родителя -> узел - единственный элемент -> нет предыдущего 
		{
			*leaf = nullptr;
			return;
		}

		int sonId = (*parent)->GetSonIdToFindNode((*leaf)->key);
		if (sonId > 0) //если узел не первый сын своего родителя, возвращаем предыдущего сына
		{
			*leaf = static_cast<Leaf*>((*parent)->sons[--sonId]);
			return;
		}

		//иначе - ищем последнее место, где поиск нашего листа происходит не через первого сына, т.е. корень соседнего (слева) поддерева
		Internal* curRoot = static_cast<Internal*>(root);
		Internal* leftNode = nullptr;
		while (curRoot->AreSonsLeafs() == false)
		{
			int id = curRoot->GetSonIdToFindNode((*leaf)->key);
			if (id != 0)
			{
				leftNode = static_cast<Internal*>(curRoot->sons[id - 1]);
			}

			curRoot = static_cast<Internal*>(curRoot->sons[id]);
		}

		if (leftNode == nullptr)
		{
			*parent = nullptr;
			*leaf = nullptr;
			return;
		}

		while (leftNode->AreSonsLeafs() == false) //самый правый сын с листами
			leftNode = static_cast<Internal*>(leftNode->sons.back());

		*parent = leftNode;
		*leaf = static_cast<Leaf*>(leftNode->sons.back()); //самый правый лист
	}
}