#pragma once 
#include "List.h"

using namespace Lab1;

template<class T>
inline Lab1::List<T>::List(int capacity)
{
	array = new Node[capacity];
	InitializeArray(array, capacity);
	this->capacity = capacity;
}

template<class T>
inline List<T>::List(const List<T>& list)
{
	if (list.IsEmpty())
		return;

	this->capacity = list.capacity;
	array = new Node[capacity];
	InitializeArray(array, capacity);

	for (int i = 0, index = list.startIndex; i < list.size; i++)
	{
		this->Add(list.array[index].value);
		index = list.array[index].nextIndex;
	}

	startIndex = 0;
	endIndex = size - 1;

	firstFreeIndex = (size < capacity ? size : NO_INDEX);
}

template<class T>
inline void List<T>::Clear()
{
	while (size > 0)
		Remove(array[startIndex]);
}

template<class T>
inline bool Lab1::List<T>::ChangeCapacity(int newCapacity)
{
	if (newCapacity <= 0 || capacity == newCapacity)
		return false;

	capacity = newCapacity;
	if (size > capacity)
		size = capacity;

	Node* newArray = new Node[capacity];
	InitializeArray(newArray, capacity);

	Node node;

	if (IsEmpty())
		goto end;

	node = array[startIndex];

	for (int i = 0; i < size; i++, node = array[node.nextIndex])
		newArray[i].value = node.value;

	startIndex = 0;
	endIndex = size - 1;

	end:

	delete array;
	array = newArray;

	for (int i = 0; i < size - 1; i++)
		LinkAsPrevAndNext(i, i + 1);

	firstFreeIndex = (size < capacity ? size : NO_INDEX);

	return true;
}

template<class T>
inline bool List<T>::Contains(T value) const
{
	int nodeIndex, pos;
	return FindNodeByValue(nodeIndex, pos, value);
}

template<class T>
inline T& List<T>::operator[](const int pos)
{
	int nodeIndex;
	if (FindNodeByPos(nodeIndex, pos))
		return array[nodeIndex].value;
	else
		throw "Wrong pos";
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
	if (size == capacity)
		return false;

	if (pos == size)
		return Add(value);

	int nodeIndex;
	if (FindNodeByPos(nodeIndex, pos) == false)
		return false;

	Node& nextNode = array[nodeIndex];

	int prevIndex = nextNode.prevIndex;

	int newNodeIndex;
	Node& newNode = GetFreeNode(newNodeIndex);
	newNode.value = value;

	bool isFirst = prevIndex == NO_INDEX;

	if (isFirst)
		this->startIndex = newNodeIndex;
	else
		LinkAsPrevAndNext(prevIndex, newNodeIndex);

	LinkAsPrevAndNext(newNodeIndex, nextNode.index);
	size++;

	return true;
}

template<class T>
inline int List<T>::GetPos(T value) const
{
	int nodeIndex, pos;
	if (FindNodeByValue(nodeIndex, pos, value) == false)
		throw "Didn't find value";

	return pos;
}

template<class T>
void List<T>::Remove(Node& node)
{
	int prevIndex = node.prevIndex, nextIndex = node.nextIndex;

	if (size == 1)
	{
		this->startIndex = endIndex = NO_INDEX;
		goto addNodeToFree;
	}

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
inline void List<T>::InitializeArray(Node* nodes, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		nodes[i].index = i;
		nodes[i].nextIndex = i + 1;
	}
	nodes[size - 1].index = size - 1;
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
inline bool List<T>::LinkAsPrevAndNext(int index1, int index2)
{
	if (index1 < 0 || index1 >= capacity || index2 < 0 || index2 >= capacity)
		return false;

	array[index1].nextIndex = index2;
	array[index2].prevIndex = index1;
	return true;
}

template<class T>
inline bool List<T>::FindNodeByPos(int &index, int pos) const
{
	if (pos < 0 || pos >= size)
		return false;

	bool reverseBypass = false;
	int curPos = 0;
	int curIndex = startIndex;

	if (pos > size / 2)
	{
		curIndex = endIndex;
		curPos = size - 1;
		reverseBypass = true;
	}

	while (curPos != pos)
	{
		if (reverseBypass)
		{
			curIndex = array[curIndex].prevIndex;
			curPos--;
		}
		else
		{
			curIndex = array[curIndex].nextIndex;
			curPos++;
		}
	}

	index = curIndex;
	return true;
}

template<class T>
inline bool List<T>::FindNodeByValue(int &index, int& pos,T value) const
{
	if (IsEmpty())
		return false;

	int curIndex = startIndex;
	int curPos = 0;
	do
	{
		if (array[curIndex].value == value)
		{
			index = curIndex;
			pos = curPos;
			return true;
		}
		curPos++;
		curIndex = array[curIndex].nextIndex;
	} while (curIndex != NO_INDEX);

	return false;
}

template<class T>
inline bool List<T>::RemoveByValue(T value)
{
	int nodeIndex, pos;
	if (FindNodeByValue(nodeIndex, pos, value) == false)
		return false;

	Remove(array[nodeIndex]);
	return false;
}

template<class T>
inline bool List<T>::RemoveByPos(int pos)
{
	int nodeIndex;
	if (FindNodeByPos(nodeIndex, pos) == false)
		return false;

	Remove(array[nodeIndex]);
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

/*
template<class T>
inline void Lab1::List<T>::PrintArray()
{
	std::cout << "------------" << std::endl;

	for (int i = 0; i < capacity; i++)
		printf("Value:%d PrevIndex:%d Index:%d NextIndex:%d\n", array[i].value, array[i].prevIndex, array[i].index, array[i].nextIndex);

	std::cout << "------------" << std::endl;
}
*/

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
	if (current->prevIndex == NO_INDEX)
		return false;

	current = &list.array[current->prevIndex];
	return true;
}

template<class T>
inline bool  List<T>::Iterator::operator==(List<T>::Iterator iterator)
{
	return this->current == iterator->current;
}

template<class T>
inline bool  List<T>::Iterator::operator!=(List<T>::Iterator iterator)
{
	return this->current != iterator->current;
}