#pragma once 
#include "List.h"

using namespace Lab1;

template<class T>
inline Lab1::List<T>::List(int capacity)
{
	array = new Node[capacity];
	for (int i = 0; i < capacity - 1; i++)
	{
		array[i].index = i;
		array[i].nextIndex = i + 1;
	}
	this->capacity = capacity;
}

template<class T>
inline List<T>::List(const List<T>& list)
{
	Clear();

	if (list.isEmpty())
		return;

	Iterator iter = list.Begin();

	do
	{
		Add(*iter);
	} 
	while (iter++);

}

template<class T>
inline void List<T>::Clear()
{
	if (IsEmpty())
		return;

	size = 0;
	startIndex = endIndex = NO_INDEX;

	Iterator iter = this->Begin();
	do
	{
		Remove(*iter.current);
	} while (iter++);

}

template<class T>
inline bool List<T>::Contains(T value)
{
	if (IsEmpty())
		return false;

	Iterator iter = this->Begin();

	do
	{
		if (*iter == value)
			return true;
	} while (iter++);

	return false;
}

template<class T>
inline T& List<T>::operator[](const int pos)
{
	if (pos < 0 || pos >= size)
		throw std::out_of_range("Wrong pos");

	Iterator iter = this->Begin();
	int currentPos = 0;

	do
	{
		if (currentPos == pos)
			return *iter;

		currentPos++;
	} while (iter++);

	throw "Unknown error";
}

template<class T>
inline bool List<T>::Add(T value)
{
	if (size == capacity)
		return false;

	int freeIndex;
	Node& node = GetFreeNode(freeIndex);
	node.value = value;

	if (IsEmpty())
		startIndex = freeIndex;
	else
		LinkAsPrevAndNext(endIndex, freeIndex);

	endIndex = freeIndex;

	size++;
	return true;
}

template<class T>
inline bool List<T>::Add(T value, int pos)
{
	if (pos < 0 || pos > size || size == capacity)
		return false;

	if (pos == size)
		return Add(value);

	Iterator iter = this->Begin();
	int currentPos = 0;

	do
	{
		if (currentPos == pos)
		{
			int prevIndex = iter.current->prevIndex;

			int nextNodeIndex = iter.current->index;

			int newNodeIndex;
			Node& node = GetFreeNode(newNodeIndex);
			node.value = value;

			bool isFirst = prevIndex == NO_INDEX;

			if (isFirst)
				this->startIndex = newNodeIndex;
			else
				LinkAsPrevAndNext(prevIndex, newNodeIndex);

			LinkAsPrevAndNext(newNodeIndex, nextNodeIndex);
			size++;
			return true;
		}
		currentPos++;
		
	} while (iter++);

	return false;
}

template<class T>
inline int List<T>::GetPos(T value)
{
	if (IsEmpty())
		throw "List is empty";

	Iterator iter = this->Begin();
	int curPosition = 0;

	do
	{
		if (*iter == value)
		{
			return curPosition;
		}
		curPosition++;
	} while (iter++);

	throw "Wrond value";
}

template<class T>
void List<T>::Remove(Node& node)
{
	int prevIndex;
	int nextIndex;

	if (size == 1)
	{
		this->startIndex = endIndex = NO_INDEX;
		goto addNodeToFree;
	}

	prevIndex = node.prevIndex;
	nextIndex = node.nextIndex;

	if (prevIndex != NO_INDEX && nextIndex != NO_INDEX)
	{
		LinkAsPrevAndNext(prevIndex, nextIndex);
	}
	else if (prevIndex == NO_INDEX)
	{
		this->startIndex = nextIndex;
		array[nextIndex].prevIndex = NO_INDEX;		
	}
	else if (nextIndex == NO_INDEX)
	{
		this->endIndex = prevIndex;
		array[prevIndex].nextIndex = NO_INDEX;
	}

	addNodeToFree:

	node.ResetIndexes();
	node.nextIndex = this->firstFreeIndex;
	firstFreeIndex = node.index;
	size--;
}

template<class T>
inline typename List<T>::Node& List<T>::GetFreeNode(int &index)
{
	index = firstFreeIndex;
	Node& freeNode = array[firstFreeIndex];
	firstFreeIndex = array[firstFreeIndex].nextIndex;
	freeNode.ResetIndexes();

	return freeNode;
}

template<class T>
inline bool Lab1::List<T>::LinkAsPrevAndNext(int index1, int index2)
{
	if (index1 < 0 || index1 >= capacity || index2 < 0 || index2 >= capacity)
		return false;
	array[index1].nextIndex = index2;
	array[index2].prevIndex = index1;
	return true;
}

template<class T>
inline bool List<T>::RemoveByValue(T value)
{
	Iterator iter = this->Begin();

	do
	{
		if (*iter == value)
		{		
			Remove(*iter.current);
			return true;
		}
	} while (iter++);

	return false;
}

template<class T>
inline bool List<T>::RemoveByPos(int pos)
{
	if (pos < 0 || pos >= size)
		return false;

	Remove(array[pos]);

	return true;
}

template<class T>
inline typename List<T>::Iterator List<T>::Begin()
{
	Iterator iter(*this, this->startIndex);
	return iter;
}

template<class T>
inline  typename List<T>::Iterator List<T>::End()
{
	Iterator iter(*this, this->endIndex);
	return iter;
}

template<class T>
inline void List<T>::Print()
{
	Iterator iter = this->Begin();
	std::cout << "{ ";

	if (IsEmpty())
		goto end;
	do
	{
		std::cout << "[" << *iter << "] ";
	} 
	while (iter++);

	end:
	std::cout << "}";
	std::cout << std::endl;
}

template<class T>
inline bool List<T>::Iterator::operator++(int)
{
	if (current->nextIndex == NO_INDEX)
		return false;

	current = &list.array[current->nextIndex];
	return true;
}

template<class T>
inline bool List<T>::Iterator::operator--(int)
{
	if (current.prevIndex == NO_INDEX)
		return false;

	current = &list.array[current->prevIndex];
	return true;
}

template<class T>
inline bool  List<T>::Iterator::operator==(List<T>::Iterator iterator)
{
	return this->list == iterator.list && this->current == iterator.current;
}

template<class T>
inline bool  List<T>::Iterator::operator!=(List<T>::Iterator iterator)
{
	return !(*this == iterator);
}

template<class T>
inline bool List<T>::Node::operator==(Node node)
{
	return this->value == node.value && this->nextIndex == node.nextIndex
		&& this->prevIndex == node.prevIndex;
}

template<class T>
inline bool List<T>::Node::operator!=(Node node)
{
	return !(*this == node);
}
