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
			Iterator(BST& bst) { this->bst = &bst;  }
			Data& operator *();
			bool operator++(int value);
			bool operator--(int value);
			bool operator == (Iterator iterator);
			bool operator != (Iterator iterator) { return !(*this == iterator); }
		protected:
			BST* bst = nullptr;
			Node* current = nullptr;

			friend class BST;
		};

		class ReverseIterator : Iterator
		{
		public:
			ReverseIterator();
			ReverseIterator(BST& bst, Node& node);
			bool operator++(int value) { this->Iterator::operator--(value); }
			bool operator--(int value) { this->Iterator::operator++(value); }

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
		void MergeWith(const BST<Key,Data>& bst);

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
		void GetNodesList(Lab1::List<Node*>& list) ;
		Node* Join(Node* myRoot, Node* anotherRoot, int& readedElements);
		void Remove(Node* node, Node* parent);
		Node* InsertRoot(Node* root, Key key, Data value, bool& isInserted);
		Node* RotateRight(Node* node);
		Node* RotateLeft(Node* node);
		Node* GetParent(Node* root, Node* node);
		Node* GetPrev(Node* node);
		Node* GetNext(Node* node);


		class Node
		{
		public:
			Node(Key key, Data value) : key(key), value(value) {};
			Key key;
			Data value;
			Node* left;
			Node* right;
			Node* GetMaxInChild() {
				if (this->right == nullptr)
					return nullptr;

				Node* max = this->right;
				while (max != nullptr)
					max = this->right;

				return max;
			}
			Node* GetMinInChild() {
				if (this->left == nullptr)
					return nullptr;

				Node* min = this->left;
				while (min != nullptr)
					min = this->left;

				return min;
			}
		};

		friend class Iterator;
		friend class ReverseIterator;
	};
}

#pragma once 
#include "BSTmethods.h"