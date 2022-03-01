#pragma once 
#include "List.h"

using namespace Lab1;

template<class T>
inline Lab1::List<T>::List(int capacity)
{
	array = new Node[capacity];
	this->capacity = capacity;
}

template<class T>
inline List<T>::List(const List<T>& list)
{
	Clear();

	if (list.isEmpty())
	{
		return;
	}

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

	Iterator iter = this->Begin();
	do
	{
		iter.current.MakeEmpty();
	} while (iter++);

	startIndex = NO_INDEX;
	endIndex = NO_INDEX;
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
}

template<class T>
inline bool List<T>::Add(T value, int pos)
{
	if (pos < 0 || pos > size || size == capacity)
		return false;

	if (pos == size)
	{
		return Add(value);
	}

	Iterator iter = this->Begin();
	int currentPos = 0;
	int currentIndex = startIndex;

	do
	{
		if (currentPos == pos)
		{
			int prevIndex = iter.current.prevIndex;

			Node newNode(value, prevIndex, currentIndex);
			int newNodeIndex = FindFreeIndex();
			array[newNodeIndex] = newNode;

			bool isFirst = prevIndex == NO_INDEX;

			if (isFirst)
				this->startIndex = newNodeIndex; 
			else
				array[prevIndex].nextIndex = newNodeIndex;

			array[currentIndex].prevIndex = newNodeIndex;
			if (currentIndex == size - 1)
				this->endIndex = currentIndex;

			size++;
			return true;
		}
		currentPos++;
		currentIndex = array[currentIndex].nextIndex;
	} while (iter++);

	return false;
}

template<class T>
inline bool List<T>::Add(T value)
{
	if (size == capacity)
		return false;

	Node newNode(value, this->endIndex, NO_INDEX);
	int freeIndex = FindFreeIndex();
	array[freeIndex] = newNode;

	array[endIndex].nextIndex = freeIndex;
	endIndex = freeIndex;

	if (IsEmpty())
		startIndex = freeIndex;

	size++;
	return true;
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
	if (size == 1)
	{
		startIndex = endIndex = NO_INDEX;
		size--;
		return;
	}

	int nodePrevIndex = node.prevIndex;
	int nodeNextIndex = node.nextIndex;

	if (nodePrevIndex == NO_INDEX)
		startIndex = nodeNextIndex;	
	else
		array[nodePrevIndex].nextIndex = nodeNextIndex;

	if (nodeNextIndex == NO_INDEX)
		endIndex = nodePrevIndex;		
	else
		array[nodeNextIndex].prevIndex = nodePrevIndex;

	node.MakeEmpty();

	size--;
}

template<class T>
inline int List<T>::FindFreeIndex()
{
	if (size == capacity)
		return NO_INDEX;

	if (size == 1)
		return (startIndex == 0 ? 1 : 0);

	for (int i = 0, j = capacity - 1; i <= j; i++, j--)
	{
		if (array[i].IsEmpty())
			return i;
		if (array[j].IsEmpty())
			return j;
	}

	return NO_INDEX;
}

template<class T>
inline bool Lab1::List<T>::LinkAsPrevAndNext(int index1, int index2)
{
	if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size)
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
			Remove(iter.current);
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
	Iterator iter(*this, startIndex);
	return iter;
}

template<class T>
inline  typename List<T>::Iterator List<T>::End()
{
	Iterator iter(*this, endIndex);
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
	if (current.nextIndex == NO_INDEX)
		return false;

	current = list.array[current.nextIndex];
	return true;
}

template<class T>
inline bool List<T>::Iterator::operator--(int)
{
	if (current.prevIndex == NO_INDEX)
		return false;

	current = list.array[current.prevIndex];
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
