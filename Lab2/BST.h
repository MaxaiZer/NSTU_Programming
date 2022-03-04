#include "../Lab1/List.h"

namespace Lab2
{

	template <class Key, class Data> 
	class BST
	{
		class Node;

	public:
		class Iterator
		{
		public:
			Iterator();
			Iterator(BST& bst, Node& node);
			T& operator *();
			bool operator++(int value);
			bool operator--(int value);
			bool operator == (Iterator iterator);
			bool operator != (Iterator iterator);
		protected:
			bool isInstalled = false;
			BST* bst;
			Node* current;

			friend class BST;
		};

		class ReverseIterator : Iterator
		{
		public:
			ReverseIterator();
			ReverseIterator(BST& bst, Node& node);
			bool operator++(int value) { this->Iterator::operator--(value); }
			bool operator--(int value) { this->Iterator::operator++(value); }
			bool operator == (ReverseIterator iterator);
			bool operator != (ReverseIterator iterator);

			friend class BST;
		};

		BST();
		BST(const& BST bst);
		~BST();
		int GetSize() const { return size; }
		void Clear();
		bool IsEmpty() const { return size == 0; }
		Data& operator[] (Key key);
		bool Add(Key key, Data value);
		bool Remove(Key key);
		Lab1::List<Data> GetNodesList() const;
		int GetReadedElementsCount() const { return readedElements; }
		void Print();

		Iterator Begin();
		Iterator End();
		ReverseIterator Rbegin();
		ReverseIterator Rend();
	protected:
		int size = 0;
		int readedElements = 0;
		Node* root = nullptr;
		bool FindNodeByKey(Node* resultParent, Node* resultNode, Key key);

		class Node
		{
		public:
			Node(Key key, Data value) : key(key), value(value) {};
			Key key;
			Data value;
			Node* left;
			Node* right;
		};

		friend class Iterator;
		friend class ReverseIterator;
	};
}

#pragma once 
#include "BSTmethods.h"
