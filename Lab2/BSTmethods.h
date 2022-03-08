#pragma once 
#include "BST.h"
#include <stack>

using namespace Lab2;

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
	GetNodesList(nodes);

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
inline typename BST<Key, Data>::Node* BST<Key, Data>::InsertRoot(Node* curRoot, Key key, Data value, bool& isInserted)
{
	if (curRoot == nullptr)
	{
		isInserted = true;
		return new Node(key, value);
	}
	if (key == curRoot->key)
	{
		isInserted = false;
		return curRoot;
	}
	if (key < curRoot->key)
	{
		curRoot->left = InsertRoot(curRoot->left, key, value, isInserted);
		return (isInserted ? RotateRight(curRoot) : curRoot);
	}
	else
	{
		curRoot->right = InsertRoot(curRoot->right, key, value, isInserted);
		return (isInserted ? RotateLeft(curRoot) : curRoot);
	}

	return nullptr;
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
inline typename BST<Key,Data>::Node* BST<Key, Data>::GetPrev(Node* node)
{
	if (node->left != nullptr)
		return node->left->GetMaxInChild();

	return GetParent(this->root, node);
}

template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetParent(Node* root, Node* node)
{
	if (node == nullptr)
		return nullptr;

	Node* parent;
	if (node->key > root->key)
	{
		parent = GetParent(node->right, node);
		return (parent != nullptr ? parent : root);
	}
	else
		return GetParent(root->left, node);
}


template<class Key, class Data>
inline typename BST<Key, Data>::Node* BST<Key, Data>::GetNext(Node* node)
{
	if (node->right != nullptr)
		return node->right->GetMinInChild();

	return GetParent(this->root, node);
}

template<class Key, class Data>
inline Lab1::List<Key> BST<Key, Data>::GetKeysList()
{
	if (IsEmpty())
		return Lab1::List<Key>();

	Lab1::List<Key> keys(this->size);
	Lab1::List<Node*> nodes(this->size);
	GetNodesList(nodes);

	typename Lab1::List<Node*>::Iterator iter = nodes.Begin();
	do
	{
		keys.Add((*iter)->key);
	} while (iter++);

	return keys;
}

template<class Key, class Data>
inline void BST<Key, Data>::GetNodesList(Lab1::List<BST::Node*>& list)
{
	list.Clear();

	TreeBypass(root, list);
}

template<class Key, class Data>
inline void BST<Key, Data>::TreeBypass(Node* root, Lab1::List<Node*>& list)
{
	if (root == nullptr)
		return;

	TreeBypass(root->left, list);
	TreeBypass(root->right, list);

	list.Add(root);
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
	int _readedElements = 0;
	this->root = Join(this->root, bst.root, _readedElements);
	readedElements = _readedElements;
}

template<class Key, class Data>
inline typename BST<Key,Data>::Node* BST<Key, Data>::Join(Node* myRoot, Node* anotherRoot, int& readedElements)
{
	if (myRoot == nullptr)
		return anotherRoot;
	if (anotherRoot == nullptr)
		return root;

	Node* left = myRoot->left;
	Node* right = myRoot->right;

	myRoot->left = nullptr;
	myRoot->right = nullptr;

	if (myRoot->key == anotherRoot->key)
	{
		Remove(myRoot, nullptr);
		readedElements += this->readedElements;
		return anotherRoot;
	}

	bool isInserted = false;
	anotherRoot = InsertRoot(anotherRoot, myRoot->key, myRoot->value, isInserted);
	anotherRoot->left = Join(left, anotherRoot->left, readedElements);
	anotherRoot->right = Join(right, anotherRoot->right, readedElements);
	
	return anotherRoot;
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
inline bool BST<Key, Data>::Iterator::operator++(int value)
{
	current = bst->GetNext(current);

	return current != nullptr;
}

template<class Key, class Data>
inline bool BST<Key, Data>::Iterator::operator--(int value)
{
	current = bst->GetPrev(current);

	return current != nullptr;
}

template<class Key, class Data>
inline Data& BST<Key, Data>::Iterator::operator*()
{
	if (current != nullptr)
		return current->value;
	else
		throw "Iterator is not installed";
}