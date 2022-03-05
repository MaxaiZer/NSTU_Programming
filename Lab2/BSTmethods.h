#pragma once 
#include "BST.h"

using namespace Lab2;

template<class Key, class Data>
inline BST<Key, Data>::BST(const BST<Key, Data>& bst)
{
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
		delete* iter;
	} while (iter++);

	size = 0;
	root = nullptr;
}

template<class Key, class Data>
inline Data& Lab2::BST<Key, Data>::operator[](Key key)
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

	Node* replaceNode;
	bool noLeft = nodeToRemove->left == nullptr;
	bool noRight = nodeToRemove->right == nullptr;

	if (noLeft && noRight)
		replaceNode = nullptr;
	else if (noLeft)
		replaceNode = nodeToRemove->right;
	else if (noRight)
		replaceNode = nodeToRemove->left;
	else
	{
		parent = nodeToRemove;
		Node* y = nodeToRemove->right;

		readedElements++;
		while (y->left != nullptr)
		{
			parent = y;
			y = y->left;
			readedElements++;
		}
		nodeToRemove->key = y->key;
		nodeToRemove->value = y->value;
		replaceNode = y->right;
		nodeToRemove = y;
	}


	if (parent == nullptr)
		this->root = replaceNode;
	else
	{
		if (nodeToRemove->key < parent->key)
			parent->left = replaceNode;
		else
			parent->right = replaceNode;
	}
	delete nodeToRemove;
	size--;
	return true;
}

template<class Key, class Data>
inline Lab1::List<Key> Lab2::BST<Key, Data>::GetKeysList()
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
}

template<class Key, class Data>
inline void Lab2::BST<Key, Data>::GetNodesList(Lab1::List<BST::Node*>& list)
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
