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

	Node* node = bst.root;
	std::stack<Node*> _stack;
	_stack.push(node);

	while (_stack.empty() == false)
	{
		node = _stack.top();
		_stack.pop();

		Add(node->key, node->value);

		if (node->left != nullptr)
			_stack.push(node->left);
		if (node->right != nullptr)
			_stack.push(node->right);

	}
}

template<class Key, class Data>
inline void BST<Key, Data>::Clear()
{
	if (IsEmpty())
		return;

	Lab1::List<Node*> nodes(this->size);
	BypassCode codes[] = { L, T, R };
	TreeBypass(this->root, nodes, codes);

	typename Lab1::List<Node*>::Iterator iter = nodes.Begin();
	do
	{
			delete *iter;
	} while (iter++);

	size = 0;
	root = nullptr;
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
		prevNode = curRoot;
		if (curRoot->key == key)
			return false;
		if (curRoot->key > key)
			curRoot = curRoot->left;
		else
			curRoot = curRoot->right;

		readedElements++;
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
	Lab1::List<Node*> nodes(this->size);

	BypassCode variant8Codes[] = { L, R, T };
	TreeBypass(this->root, nodes, variant8Codes);

	typename Lab1::List<Node*>::Iterator iter = nodes.Begin();
	do
	{
		keys.Add((*iter)->key);
	} while (iter++);

	return keys;
}

template<class Key, class Data>
inline void BST<Key, Data>::Print()
{
	PrintLevels(root, 0);
	std::cout << std::endl;
}

template<class Key, class Data>
inline void BST<Key, Data>::MergeWith(const BST<Key, Data>& bst)
{
	if (bst.IsEmpty())
		return;

	BST<Key, Data> myCopy(*this);
	Clear();

	Lab1::List<Node*> nodes1(bst.size);
	Lab1::List<Node*> nodes2(myCopy.size);

	BypassCode codes[3] = { L, T, R };
	bst.TreeBypass(bst.root, nodes1, codes);
	myCopy.TreeBypass(myCopy.root, nodes2, codes);

	Node** sortedArray = new Node*[nodes1.GetSize() + nodes2.GetSize()];
	int sortedArraySize = 0;
	int _readedElements = myCopy.GetReadedElementsCount() + nodes1.GetSize() + nodes2.GetSize();

	//добавляем в sortedArray только уникальные ключи из nodes1 и nodes2
	while (nodes1.GetSize() + nodes2.GetSize() != 0)
	{
		if (nodes1.GetSize() == 0)
		{
			sortedArray[sortedArraySize++] = nodes2[0];
			nodes2.RemoveByPos(0);
		}
		else if (nodes2.GetSize() == 0)
		{
			sortedArray[sortedArraySize++] = nodes1[0];
			nodes1.RemoveByPos(0);
		}
		else if (nodes1[0]->key < nodes2[0]->key)
		{
			sortedArray[sortedArraySize++] = nodes1[0];
			nodes1.RemoveByPos(0);
		}
		else if (nodes1[0]->key > nodes2[0]->key)
		{
			sortedArray[sortedArraySize++] = nodes2[0];
			nodes2.RemoveByPos(0);
		}
		else
			nodes1.RemoveByPos(0);
	}

	this->root = new Node();
	_readedElements += sortedArraySize;
	CreateFromSortedArray(sortedArray, this->root, 0, sortedArraySize - 1);
	_readedElements += sortedArraySize;

	readedElements = _readedElements;

	delete sortedArray;
}

template<class Key, class Data>
inline  typename BST<Key, Data>::Iterator BST<Key, Data>::Begin()
{
	Node* min;
	if (root == nullptr)
		min = nullptr;
	else
	{
		min = root->GetMinInChild();
		min = (min == nullptr ? root : min);
	}
	Iterator iter(*this, min);
	return iter;
}

template<class Key, class Data>
inline  typename BST<Key, Data>::Iterator BST<Key, Data>::End()
{
	Iterator iter(*this, nullptr);
	return iter;
}

template<class Key, class Data>
inline  typename BST<Key, Data>::ReverseIterator BST<Key, Data>::Rbegin()
{
	Node* max;
	if (root == nullptr)
		max = nullptr;
	else
	{
		max = root->GetMaxInChild();
		max = (max == nullptr ? root : max);
	}
	ReverseIterator iter(*this, max);
	return iter;
}

template<class Key, class Data>
inline  typename BST<Key, Data>::ReverseIterator BST<Key, Data>::Rend()
{
	ReverseIterator iter(*this, nullptr);
	return iter;
}

//приватные методы дерева

template<class Key, class Data>
inline bool BST<Key, Data>::FindNodeByKey(Node** resultParent, Node** resultNode, Key key)
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
	Node* replaceNode;
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
		parent = node;
		Node* y = node->right;

		readedElements++;
		while (y->left != nullptr)
		{
			parent = y;
			y = y->left;
			readedElements++;
		}
		node->key = y->key;
		node->value = y->value;
		replaceNode = y->right;
		node = y;
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
inline typename BST<Key, Data>::Node* BST<Key, Data>::RotateRight(Node* node)
{
	if (node == nullptr)
		return nullptr;

	Node* newNode = node->left;
	node->left = newNode->right;
	newNode->right = node;
	return newNode;
}

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::RotateLeft(Node* node)
{
	if (node == nullptr)
		return nullptr;

	Node* newNode = node->right;
	node->right = newNode->left;
	newNode->left = node;
	return newNode;
}

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetPrev(Node* node)
{
	if (node->left != nullptr)
		return node->left->GetMaxInChild();

	return GetParent(this->root, node);
}

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetParent(Node* root, Node* node)
{
	if (root == node)
		return nullptr;

	Node* parent;
	if (node->key > root->key)
		parent = GetParent(root->right, node);
	else
		parent = GetParent(root->left, node);

	return (parent != nullptr ? parent : root);
}

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetNext(Node* node)
{
	if (node->right != nullptr)
	{
		Node* min = node->right->GetMinInChild();
		return (min == nullptr ? node->right : min);
	}

	Node* current = this->root;
	Node* lastSuccessNode = nullptr;

	while (current != nullptr)
	{
		if (current->key > node->key)
		{ 
			//спуск в левое поддерево
			lastSuccessNode = current;
			current = current->left;
		}
		else
		{
			//спуск в правое поддерево
			current = current->right;
		}
	}

	return lastSuccessNode;
}

template<class Key, class Data>
inline void Lab2::BST<Key, Data>::CreateFromSortedArray(Node** array, Node* currentNode, int l, int r)
{
	int mid = (l + r) / 2;

	currentNode->key = array[mid]->key;
	currentNode->value = array[mid]->value;
	size++;

	if (mid - 1 >= l)
	{
		currentNode->left = new Node();
		CreateFromSortedArray(array, currentNode->left, l, mid - 1);
	}

	if (mid + 1 <= r)
	{
		currentNode->right = new Node();
		CreateFromSortedArray(array, currentNode->right, mid + 1, r);
	}
}

template<class Key, class Data>
inline void BST<Key, Data>::PrintLevels(Node* root, int level)
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
inline void BST<Key, Data>::TreeBypass(Node* root, Lab1::List<Node*>& list, BypassCode codes[3]) const
{
	if (root == nullptr)
		return;

	for (int i = 0; i < 3; i++)
	{
		if (codes[i] == BypassCode::L)
			TreeBypass(root->left, list, codes);
		else if (codes[i] == BypassCode::R)
			TreeBypass(root->right, list, codes);
		else if (codes[i] == BypassCode::T)
			list.Add(root);
	}
}

//методы итераторов

template<class Key, class Data>
inline bool BST<Key, Data>::Iterator::operator++(int value)
{
	return (current = bst->GetNext(current)) != nullptr;
}

template<class Key, class Data>
inline bool BST<Key, Data>::Iterator::operator--(int value)
{
	return (current = bst->GetPrev(current)) != nullptr;
}

template<class Key, class Data>
inline Data& BST<Key, Data>::Iterator::operator*()
{
	if (current != nullptr)
		return current->value;
	else
		throw "Iterator is not installed";
}

template<class Key, class Data>
inline bool Lab2::BST<Key, Data>::ReverseIterator::operator++(int value)
{
	return (current = bst->GetPrev(current)) != nullptr;
}

template<class Key, class Data>
inline bool Lab2::BST<Key, Data>::ReverseIterator::operator--(int value)
{
	return (current = bst->GetNext(current)) != nullptr;
}

template<class Key, class Data>
inline Data& Lab2::BST<Key, Data>::ReverseIterator::operator*()
{
	if (current != nullptr)
		return current->value;
	else
		throw "Iterator is not installed";
}