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
			Iterator() {};
			Iterator(BST& bst, Node* node) { this->bst = &bst; current = node; }
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

		class ReverseIterator : public Iterator
		{
		public:
			ReverseIterator() {};
			ReverseIterator(BST& bst, Node* node) : Iterator(bst, node) {};
			bool operator++(int value) { return this->Iterator::operator--(value); }
			bool operator--(int value) { return this->Iterator::operator++(value); }

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
		Lab1::List <BST<Key, Data>*> copiedTrees;
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
			Node() {};
			Node(Key key, Data value) : key(key), value(value) {};
			Node& operator=(const Node& node) { 
				key = node.list; value = node.value;
				left = node.left; right = node.right;
				return *this;
			};
			Key key;
			Data value;
			Node* left = nullptr;
			Node* right = nullptr;
			Node* GetMaxInChild() {
				if (this->right == nullptr)
					return nullptr;

				Node* max = this->right;
				while (max->right != nullptr)
					max = max->right;

				return max;
			}
			Node* GetMinInChild() {
				if (this->left == nullptr)
					return nullptr;

				Node* min = this->left;
				while (min->left != nullptr)
					min = min->left;

				return min;
			}
		};

		friend class Iterator;
		friend class ReverseIterator;
	};
}

#pragma once 
#include "BSTmethods.h"