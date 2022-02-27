#pragma once 
#include "List.h"

template<class T>
inline List<T>::List(const List<T>& list)
{
	if (list.isEmpty())
		return;

	clear();

	Node* node = list.start;

	while (node != nullptr)
	{
		add(node->value);
		node = node->next;
	}

}

template<class T>
inline List<T>::~List()
{
	clear();
}

template<class T>
inline int List<T>::getSize() const
{
	return size;
}

template<class T>
inline bool List<T>::isEmpty() const
{
	return size == 0;
}

template<class T>
inline void List<T>::clear()
{
	if (isEmpty())
		return;

	size = 0;

	Node* node = start;

	while (node->next != nullptr)
	{
		Node* nodeToDelete = node;
		node = node->next;
		delete nodeToDelete;
	}

	delete node;
}

template<class T>
inline bool List<T>::contains(T value) const
{
	Node* node = start;

	while (node != nullptr)
	{
		if (node->value == value)
			return true;

		node = node->next;
	}

	return false;
}

template<class T>
inline bool List<T>::add(T value, int index)
{
	if (index < 0 || index > size)
		return false;

	if (index == size)
	{
		add(value);
		return true;
	}

	Node* nextNode = start;

	for (int curIndex = 0; curIndex < index; curIndex++)
		nextNode = nextNode->next;

	Node* prevNode = nextNode->prev;

	Node* newNode = new Node(value, prevNode, nextNode);

	if (prevNode != nullptr)
		prevNode->next = newNode;
	else
		start = newNode;

	if (nextNode != nullptr)
		nextNode->prev = newNode;

	size++;
	return true;
}

template<class T>
inline void List<T>::add(T value)
{
	if (isEmpty())
	{
		start = new Node(value, nullptr, nullptr);
		size++;
		return;
	}

	Node* last = start;
	while (last->next != nullptr)
		last = last->next;

	Node* newNode = new Node(value, last, nullptr);
	last->next = newNode;
	size++;
}

template<class T>
inline T List<T>::read(int index) const
{
	if (index < 0 || index > size)
		throw "Wrong index";

	Node* cur = start;

	for (int curIndex = 0; curIndex < index; curIndex++)
		cur = cur->next;

	return cur->value;
}

template<class T>
inline bool List<T>::set(T value, int index)
{
	if (index < 0 || index >= size)
		return false;

	Node* node = start;

	for (int curIndex = 0; curIndex < index; curIndex++)
		node = node->next;

	node->value = value;
	return true;
}

template<class T>
inline int List<T>::getPos(T value) const
{
	Node* node = start;
	int curIndex = 0;

	for (; node->next != nullptr; curIndex++)
	{
		if (node->value == value)
			return curIndex;

		node = node->next;
	}

	if (node->value == value)
		return curIndex;

	throw "Wrond value";
}

template<class T>
void List<T>::remove(Node* node)
{
	Node* prev = node->prev;
	Node* next = node->next;
	delete node;
	if (prev != nullptr)
		prev->next = next;
	else
		start = next;

	if (next != nullptr)
		next->prev = prev;
	size--;
}

template<class T>
inline bool List<T>::removeByValue(T value)
{
	Node* node = start;

	while (node != nullptr)
	{
		if (node->value == value)
		{
			remove(node);
			return true;
		}
		node = node->next;
	}

	return false;
}

template<class T>
inline bool List<T>::removeByPos(int index)
{
	Node* node = start;
	int curIndex = 0;

	while (node != nullptr)
	{
		if (curIndex == index)
		{
			remove(node);
			return true;
		}
		node = node->next;
		curIndex++;
	}

	return false;
}

template<class T>
inline typename List<T>::Iterator List<T>::begin()
{
	if (size == 0)
		return end();

	return List<T>::Iterator(this, start);
}

template<class T>
inline  typename List<T>::Iterator List<T>::end()
{
	return List<T>::Iterator(this, nullptr);
}

template<class T>
inline void List<T>::print()
{
	Iterator iter = this->begin();
	std::cout << "{ ";
	while (iter != this->end())
	{
		std::cout << "[" << *iter << "] ";
		iter++;
	}
	std::cout << "}";
	std::cout << std::endl;
}

template<class T>
inline List<T>::Iterator::Iterator(List<T>* list, Node* node)
{
	this->list = list;
	this->cur = node;
}

template<class T>
inline T& List<T>::Iterator::operator*()
{
	return cur->value;
}

template<class T>
inline  void List<T>::Iterator::operator++(int)
{
	if (cur->next != nullptr)
		cur = cur->next;
	else
		*this = list->end();
}

template<class T>
inline void List<T>::Iterator::operator--(int)
{
	if (cur->prev != nullptr)
		cur = cur->prev;
}

template<class T>
inline bool  List<T>::Iterator::operator==(List<T>::Iterator iterator)
{
	return this->cur == iterator.cur;
}

template<class T>
inline bool  List<T>::Iterator::operator!=(List<T>::Iterator iterator)
{
	return this->cur != iterator.cur;
}

