#pragma once 
#include "BST.h"

using namespace Lab2;

template<class Key, class Data>
inline void Lab2::BST<Key, Data>::Clear()
{

}

template<class Key, class Data>
inline bool Lab2::BST<Key, Data>::Add(Key key, Data value)
{
	return false;
}

template<class Key, class Data>
inline bool BST<Key, Data>::Remove(Key key)
{
	Node* parent, nodeToRemove;
	if (FindNodeByKey(parent, nodeToRemove, key))
	{
		//remove
		return true;
	}
	return false;
}

template<class Key, class Data>
inline Lab1::List<Data> Lab2::BST<Key, Data>::GetNodesList() const
{
	return Lab1::List();
}


template<class Key, class Data>
inline bool BST<Key, Data>::FindNodeByKey(Node* resultParent, Node* resultNode, Key key)
{
	if (IsEmpty())
		return false;

	Node* curRoot = this->root;
	Node* curParent = nullptr;

	while (curRoot != nullptr && curRoot.key != key)
	{
		curParent = curRoot;
		curRoot = (key < curRoot.key ? curRoot.left : curRoot.right);
	}

	if (curRoot == nullptr)
		return false;
	else
	{
		resultNode = curRoot;
		resultParent = curParent;
		return true;
	}
}