#pragma once 
#include "BST.h"
#include <stack>

using namespace Lab2;

//публичные методы дерева

template<class Key, class Data>
inline BST<Key, Data>::BST(const BST<Key, Data>& bst)
{
	if (bst.IsEmpty())
		return;

	BypassTree(bst.root, BypassMode::AddToTree);
}

template<class Key, class Data>
inline void BST<Key, Data>::Clear()
{
	if (IsEmpty())
		return;

	size = 0;

	BypassTree(this->root, BypassMode::DeleteFromMemory);
}

template<class Key, class Data>
inline Data& BST<Key, Data>::operator[](Key key)
{
	Node* parent = nullptr;
	Node* node = nullptr;
	if (FindNodeByKey(&parent, &node, key) == false)
		throw "Wrong key";
	else
		return node->value;
}

template<class Key, class Data>
inline bool BST<Key, Data>::Add(Key key, Data value)
{
	readedElements = 0;
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
		readedElements++;

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

template<class Key, class Data>
inline bool BST<Key, Data>::Remove(Key key)
{
	Node* parent = nullptr;
	Node* nodeToRemove = nullptr;
	if (FindNodeByKey(&parent, &nodeToRemove, key) == false)
		return false;

	Remove(nodeToRemove, parent);
	return true;
}

template<class Key, class Data>
inline Lab1::List<Key> BST<Key, Data>::GetKeysList() const
{
	if (IsEmpty())
		return Lab1::List<Key>();

	Lab1::List<Key> keys(this->size);
	Lab1::List<Node> nodes(this->size);

	BypassCode var8Codes[] = { BypassCode::L, BypassCode::R, BypassCode::T};
	AddNodesToList(this->root, nodes, var8Codes);

	typename Lab1::List<Node>::Iterator iter = nodes.Begin();
	do
	{
		keys.Add((*iter).key);
	} while (iter++);

	return keys;
}

template<class Key, class Data>
inline void BST<Key, Data>::Print() const
{
	if (IsEmpty())
	{
		std::cout << "Tree is empty" << std::endl;
		return;
	}

	PrintLevels(root, 0);
}

template<class Key, class Data>
inline void BST<Key, Data>::MergeWith(const BST<Key, Data>& bst)
{
	if (bst.IsEmpty())
		return;

	Lab1::List<Node> nodes1(bst.size);
	Lab1::List<Node> nodes2(this->size + 1); 

	BypassCode codes[3] = { BypassCode::L, BypassCode::T, BypassCode::R };

	//добавляем ключи обоих деревьев в соотв. списки в порядке возрастания

	bst.AddNodesToList(bst.root, nodes1, codes);
	this->AddNodesToList(this->root, nodes2, codes);
	
	Clear();

	Node* sortedArray = new Node[nodes1.GetSize() + nodes2.GetSize()];
	int sortedArraySize = 0;
	int _readedElements = nodes1.GetSize() + nodes2.GetSize();

	//добавляем в sortedArray только уникальные ключи из nodes1 и nodes2 в порядке возрастания
	while (nodes1.GetSize() + nodes2.GetSize() != 0)
	{
		if (nodes1.IsEmpty())
			goto addFromNodes2;
		else if (nodes2.IsEmpty())
			goto addFromNodes1;

		if (nodes1[0].key == nodes2[0].key)
		{
			nodes1.RemoveByPos(0);
			continue;
		}

		if (nodes1[0].key < nodes2[0].key)
		{
			addFromNodes1:
			sortedArray[sortedArraySize++] = nodes1[0];
			nodes1.RemoveByPos(0);
		}
		else
		{
			addFromNodes2:
			sortedArray[sortedArraySize++] = nodes2[0];
			nodes2.RemoveByPos(0);
		}
	}

	this->root = new Node();

	_readedElements += sortedArraySize;
	CreateFromSortedArray(sortedArray, this->root, 0, sortedArraySize - 1);
	_readedElements += sortedArraySize;

	readedElements = _readedElements;

	delete[] sortedArray;
}

template<class Key, class Data>
inline  typename BST<Key, Data>::Iterator BST<Key, Data>::Begin()
{
	if (IsEmpty())
		return End();

	Node* min = min = root->GetMinInChild();
	min = (min == nullptr ? root : min);

	return Iterator(*this, min);
}

template<class Key, class Data>
inline  typename BST<Key, Data>::ReverseIterator BST<Key, Data>::Rbegin()
{
	if (IsEmpty())
		return Rend();

	Node* max = root->GetMaxInChild();
	max = (max == nullptr ? root : max);

	return ReverseIterator(*this, max);
}

//приватные методы дерева

template<class Key, class Data>
inline bool BST<Key, Data>::FindNodeByKey(Node** resultParent, Node** resultNode, Key key) const
{
	if (IsEmpty())
		return false;

	Node* curRoot = this->root;
	Node* curParent = nullptr;
	readedElements = 1;

	while (curRoot != nullptr && curRoot->key != key)
	{
		curParent = curRoot;
		curRoot = (key < curRoot->key ? curRoot->left : curRoot->right);
		readedElements++;
	}

	if (curRoot == nullptr)
		return false;

	*resultNode = curRoot;
	*resultParent = curParent;
	return true;
}

template<class Key, class Data>
inline void BST<Key, Data>::Remove(Node* node, Node* parent)
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

		readedElements++;
		while (min->left != nullptr)
		{
			parent = min;
			min = min->left;
			readedElements++;
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

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetPrev(Node* node) const
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

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetParent(Node* node) const
{
	Node* resultParent = nullptr;
	Node* result = nullptr;
	if (FindNodeByKey(&resultParent, &result, node->key) == false)
		return nullptr;

	return resultParent;
}

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetNext(Node* node) const
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

template<class Key, class Data>
inline void Lab2::BST<Key, Data>::CreateFromSortedArray(Node* array, Node* currentNode, int l, int r)
{
	int mid = (l + r) / 2;

	//текущий узел - середина массива между левой и правой границей

	currentNode->key = array[mid].key;
	currentNode->value = array[mid].value;
	size++;

	if (mid - 1 >= l)
	{
		//вершина левого поддерева - середина массива между левой границей и текущим узлом
		currentNode->left = new Node(); 
		CreateFromSortedArray(array, currentNode->left, l, mid - 1);
	}

	if (mid + 1 <= r)
	{
		//вершина правого поддерева - середина массива между текущим узлом и правой границей
		currentNode->right = new Node();
		CreateFromSortedArray(array, currentNode->right, mid + 1, r);
	}
}

template<class Key, class Data>
inline void Lab2::BST<Key, Data>::BypassTree(Node* root, BypassMode mode)
{
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
			Add(node->key, node->value);
		else if (mode == BypassMode::DeleteFromMemory)
			delete node;
	}
}

template<class Key, class Data>
inline void BST<Key, Data>::PrintLevels(Node* root, int level) const
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

template<class Key, class Data>
inline void BST<Key, Data>::AddNodesToList(Node* root, Lab1::List<Node>& list, BypassCode codes[3]) const
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