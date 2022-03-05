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
			Data& operator *();
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

		BST() {};
		BST(const BST<Key, Data>& bst);
		~BST() { Clear(); }
		int GetSize() const { return size; }
		void Clear();
		bool IsEmpty() const { return size == 0; }
		Data& operator[] (Key key);
		bool Add(Key key, Data value);
		bool Remove(Key key);
		Lab1::List<Key> GetKeysList();
		int GetReadedElementsCount() const { return readedElements; }
		void Print();
		void MergeWith();

		Iterator Begin();
		Iterator End();
		ReverseIterator Rbegin();
		ReverseIterator Rend();
	protected:
		int size = 0;
		int readedElements = 0;
		Node* root = nullptr;
		void PrintLevels(Node* root, int level);
		bool FindNodeByKey(Node** resultParent, Node** resultNode, Key key);
		void TreeBypass(Node* root, Lab1::List<Node*>& list);
		void GetNodesList(Lab1::List<Node*>& list);

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
