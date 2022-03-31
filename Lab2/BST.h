#include <stack>
#include "../Lab1/List.h"

namespace Lab2
{
	#define IterNotInstalledEx "Iterator is not installed"

	template <class K, class V>  //Key, Value
	class BST
	{
		class Node;

	public:
		class Iterator
		{
		public:
			Iterator() {};
			Iterator(BST& bst, Node* node) { this->bst = &bst; current = node; }
			V& operator *() const 
			{
				if (current != nullptr)
					return current->value;

				throw IterNotInstalledEx;
			}
			bool operator++(int value) //переход к следующему узлу при прямом обходе
			{ return (current = bst->GetNext(current)) != nullptr; }	
			bool operator--(int value)  //переход к предыдущему узлу при прямом обходе
			{ return (current = bst->GetPrev(current)) != nullptr; }
			bool operator == (Iterator iter) const { return bst == iter.bst && current == iter.current; }
			bool operator != (Iterator iter) const { return !(*this == iter); }
		protected:
			BST* bst = nullptr; 
			Node* current = nullptr; 

			friend class BST;
		};

		class ReverseIterator
		{
		public:
			ReverseIterator() {};
			ReverseIterator(BST& bst, Node* node) { this->bst = &bst; current = node; }
			V& operator *() const 
			{
				if (current != nullptr)
					return current->value;
				
				throw IterNotInstalledEx;
			}
			bool operator++(int value) //переход к предыдущему узлу при прямом обходе
			{ return (current = bst->GetPrev(current)) != nullptr; }
			bool operator--(int value) // переход к следующему узлу при прямом обходе
			{ return (current = bst->GetNext(current)) != nullptr;}
			bool operator == (ReverseIterator iter) const { return bst == iter.bst && current == iter.current; }
			bool operator != (ReverseIterator iter) const { return !(*this == iter); }
		protected:
			BST* bst = nullptr;
			Node* current = nullptr;

			friend class BST;
		};

		BST() {}; 
		BST(const BST<K, V>& bst) { MergeWith(bst); };
		~BST() { Clear(); }
		int GetSize() const { return size; } 
		void Clear(); 
		bool IsEmpty() const { return size == 0; }
		V& operator[] (K key); 
		bool Add(K key, V value); 
		bool Remove(K key); 
		Lab1::List<K> GetKeysList() const; //возвращает список ключей по схеме L -> R -> t
		int GetReadElementsCount() const { return readElements; } //опрос числа узлов дерева, просмотренных предыдущей операцией
		void Print() const;
		void MergeWith(const BST<K,V>& bst);  //объединение с другим деревом

		Iterator Begin(); //запрос прямого итератора, установленного на узел дерева с минимальным ключом
		Iterator End() { return Iterator(*this, nullptr); } //запрос «неустановленного» прямого итератора
		ReverseIterator Rbegin(); //запрос обратного итератора, установленного на узел дерева с максимальным ключом
		ReverseIterator Rend() { return ReverseIterator(*this, nullptr); } //запрос «неустановленного» обратного итератора
	protected:
		int size = 0;
		mutable int readElements = 0; //число узлов дерева, просмотренных предыдущей операцией
		Node* root = nullptr;

		enum class BypassCode { L, T, R }; //для составления схемы обхода
		void AddNodesToList(Node* root, Lab1::List<Node>& list, BypassCode codes[3]) const; //добавление узлов в список по схеме обхода

		enum class BypassMode {AddToTree, DeleteFromMemory}; //режим обхода дерева
		int BypassTree(Node* root, BypassMode mode); //обход дерева, где для каждого узла выполняется действие согласно режиму обхода

		void PrintLevels(Node* root, int level) const; //рекурсивный вывод дерева
		bool FindNodeByKey(Node** resultParent, Node** resultNode, K key) const;
		void Remove(Node* node, Node* parent); 
		Node* GetParent(Node* node) const;
		Node* GetPrev(Node* node) const; //следующий узел при прямом обходе
		Node* GetNext(Node* node) const; //предыдущий узел при прямом обходе

		class Node
		{
		public:
			K key;
			V value;
			Node* left = nullptr;
			Node* right = nullptr;

			Node() {};
			Node(K key, V value) : key(key), value(value) {};

			Node* GetMaxInChild() const {
				if (this->right == nullptr)
					return nullptr;

				Node* max = this->right;
				while (max->right != nullptr)
					max = max->right;

				return max;
			}
			Node* GetMinInChild() const {
				if (this->left == nullptr)
					return nullptr;

				Node* min = this->left;
				while (min->left != nullptr)
					min = min->left;

				return min;
			}
		};

		friend class Iterator;
		friend class ReverseIterator;
	};

	//открытые методы дерева

	template<class K, class V>
	inline void BST<K, V>::Clear()
	{
		if (IsEmpty())
			return;

		size = 0;
		BypassTree(this->root, BypassMode::DeleteFromMemory);
	}

	template<class K, class V>
	inline V& BST<K, V>::operator[](K key)
	{
		Node* parent = nullptr;
		Node* node = nullptr;
		if (FindNodeByKey(&parent, &node, key) == false)
			throw "Wrong key";
		else
			return node->value;
	}

	template<class K, class V>
	inline bool BST<K, V>::Add(K key, V value)
	{
		readElements = 0;
		if (IsEmpty())
		{
			root = new Node(key, value);
			size++;
			return true;
		}

		Node* curRoot = root;
		Node* prevNode = nullptr;
		while (curRoot != nullptr)
		{
			readElements++;

			prevNode = curRoot;
			if (curRoot->key == key)
				return false;
			if (curRoot->key > key) //спуск в левое поддерево
				curRoot = curRoot->left;
			else					//спуск в правое поддерево
				curRoot = curRoot->right;
		}

		if (key < prevNode->key)
			prevNode->left = new Node(key, value);
		else
			prevNode->right = new Node(key, value);

		size++;
		return true;
	}

	template<class K, class V>
	inline bool BST<K, V>::Remove(K key)
	{
		Node* parent = nullptr;
		Node* nodeToRemove = nullptr;
		if (FindNodeByKey(&parent, &nodeToRemove, key) == false)
			return false;

		Remove(nodeToRemove, parent);
		return true;
	}

	template<class K, class V>
	inline Lab1::List<K> BST<K, V>::GetKeysList() const
	{
		if (IsEmpty())
			return Lab1::List<K>();

		Lab1::List<K> keys(this->size);
		Lab1::List<Node> nodes(this->size);

		BypassCode var8Codes[] = { BypassCode::L, BypassCode::R, BypassCode::T };
		AddNodesToList(this->root, nodes, var8Codes);

		typename Lab1::List<Node>::Iterator iter = nodes.Begin();
		do
		{
			keys.Add((*iter).key);
		} while (iter++);

		return keys;
	}

	template<class K, class V>
	inline void BST<K, V>::Print() const
	{
		if (IsEmpty())
		{
			std::cout << "Tree is empty" << std::endl;
			return;
		}

		PrintLevels(root, 0);
	}

	template<class K, class V>
	inline void BST<K, V>::MergeWith(const BST<K, V>& bst)
	{
		if (bst.IsEmpty())
			return;

		readElements = BypassTree(bst.root, BypassMode::AddToTree);
	}

	template<class K, class V>
	inline  typename BST<K, V>::Iterator BST<K, V>::Begin()
	{
		if (IsEmpty())
			return End();

		Node* min = root->GetMinInChild();
		min = (min == nullptr ? root : min);

		return Iterator(*this, min);
	}

	template<class K, class V>
	inline  typename BST<K, V>::ReverseIterator BST<K, V>::Rbegin()
	{
		if (IsEmpty())
			return Rend();

		Node* max = root->GetMaxInChild();
		max = (max == nullptr ? root : max);

		return ReverseIterator(*this, max);
	}

	//приватные методы дерева

	template<class K, class V>
	inline bool BST<K, V>::FindNodeByKey(Node** resultParent, Node** resultNode, K key) const
	{
		if (IsEmpty())
			return false;

		Node* curRoot = this->root;
		Node* curParent = nullptr;
		readElements = 1;

		while (curRoot != nullptr && curRoot->key != key)
		{
			curParent = curRoot;
			curRoot = (key < curRoot->key ? curRoot->left : curRoot->right);
			readElements++;
		}

		if (curRoot == nullptr)
			return false;

		*resultNode = curRoot;
		*resultParent = curParent;
		return true;
	}

	template<class K, class V>
	inline void BST<K, V>::Remove(Node* node, Node* parent)
	{
		Node* replaceNode; //узел, который встанет на место удалённого
		bool noLeft = node->left == nullptr;
		bool noRight = node->right == nullptr;

		if (noLeft && noRight)
			replaceNode = nullptr;
		else if (noLeft)
			replaceNode = node->right;
		else if (noRight)
			replaceNode = node->left;
		else
		{
			//поиск в правом поддереве узла с мин. ключом
			parent = node;
			Node* min = node->right;

			readElements++;
			while (min->left != nullptr)
			{
				parent = min;
				min = min->left;
				readElements++;
			}

			//значения удаляемого узла теперь равны min
			node->key = min->key;
			node->value = min->value;

			//теперь удаляемый узел - min
			//parent и replaceNode указывают на его родителя и замену
			node = min;
			replaceNode = min->right;
		}


		if (parent == nullptr)
			this->root = replaceNode;
		else
		{
			if (node->key < parent->key)
				parent->left = replaceNode;
			else
				parent->right = replaceNode;
		}
		delete node;
		size--;
	}

	template<class K, class V>
	inline typename BST<K, V>::Node* BST<K, V>::GetPrev(Node* node) const
	{
		if (node == nullptr)
			return nullptr;

		//если есть левый потомок, предыдущий - либо он, либо элемент с макс. ключом в его потомках
		if (node->left != nullptr)
		{
			Node* max = node->left->GetMaxInChild();
			return (max == nullptr ? node->left : max);
		}

		//иначе - спуск от корня с поиском элемента с макс. ключом, меньшим, чем у node
		Node* current = this->root;
		Node* lastSuccessNode = nullptr;

		while (current != nullptr)
		{
			if (current->key == node->key)
				break;

			if (current->key > node->key) //спуск в левое поддерево
			{
				current = current->left;
			}
			else //спуск в правое поддерево
			{
				lastSuccessNode = current;
				current = current->right;
			}
		}

		return lastSuccessNode;
	}

	template<class K, class V>
	inline typename BST<K, V>::Node* BST<K, V>::GetParent(Node* node) const
	{
		Node* resultParent = nullptr;
		Node* result = nullptr;

		FindNodeByKey(&resultParent, &result, node->key);
		return resultParent;
	}

	template<class K, class V>
	inline typename BST<K, V>::Node* BST<K, V>::GetNext(Node* node) const
	{
		if (node == nullptr)
			return nullptr;

		//если есть правый потомок, следующий - либо он, либо элемент с мин. ключом в его потомках
		if (node->right != nullptr)
		{
			Node* min = node->right->GetMinInChild();
			return (min == nullptr ? node->right : min);
		}
		//иначе - спуск от корня с поиском элемента с мин. ключом, большим, чем у node

		Node* current = this->root;
		Node* lastSuccessNode = nullptr;

		while (current != nullptr)
		{
			if (current->key == node->key)
				break;

			if (current->key > node->key) //спуск в левое поддерево
			{
				lastSuccessNode = current;
				current = current->left;
			}
			else //спуск в правое поддерево
			{
				current = current->right;
			}
		}

		return lastSuccessNode;
	}

	template<class K, class V>
	inline int BST<K, V>::BypassTree(Node* root, BypassMode mode)
	{
		int _readElements = 0;
		Node* node = root;
		std::stack<Node*> _stack;
		_stack.push(node);

		while (_stack.empty() == false)
		{
			node = _stack.top();
			_stack.pop();

			if (node->left != nullptr)
				_stack.push(node->left);
			if (node->right != nullptr)
				_stack.push(node->right);

			if (mode == BypassMode::AddToTree)
			{
				Add(node->key, node->value);
				_readElements += readElements;
			}
			else if (mode == BypassMode::DeleteFromMemory)
				delete node;
		}
		return _readElements;
	}

	template<class K, class V>
	inline void BST<K, V>::PrintLevels(Node* root, int level) const
	{
		if (root == nullptr)
			return;

		int levelOffset = 3;
		PrintLevels(root->right, level + 1);

		for (int i = 0; i <= levelOffset * level; i++)
		{
			printf(" ");
		}
		std::cout << root->key << std::endl;

		PrintLevels(root->left, level + 1);
	}

	template<class K, class V>
	inline void BST<K, V>::AddNodesToList(Node* root, Lab1::List<Node>& list, BypassCode codes[3]) const
	{
		if (root == nullptr)
			return;

		for (int i = 0; i < 3; i++)
		{
			if (codes[i] == BypassCode::L)
				AddNodesToList(root->left, list, codes);
			else if (codes[i] == BypassCode::R)
				AddNodesToList(root->right, list, codes);
			else if (codes[i] == BypassCode::T)
				list.Add(*root);
		}
	}

}