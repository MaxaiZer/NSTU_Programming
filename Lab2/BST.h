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
			bool operator == (Iterator iter) { return bst == iter.bst && current == iter.current; }
			bool operator != (Iterator iter) { return !(*this == iter); }
		protected:
			BST* bst = nullptr;
			Node* current = nullptr;

			friend class BST;
		};

		class ReverseIterator
		{
		public:
			ReverseIterator() {};
			ReverseIterator(BST& bst, Node* node) { this->bst = &bst; current = node; }
			Data& operator *();
			bool operator++(int value);
			bool operator--(int value);
			bool operator == (ReverseIterator iter) { return bst == iter.bst && current == iter.current; }
			bool operator != (ReverseIterator iter) { return !(*this == iter); }
		protected:
			BST* bst = nullptr;
			Node* current = nullptr;

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
		Lab1::List<Key> GetKeysList() const;
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
		const enum BypassCode { L, T, R };
		const enum BypassMode {AddToTree, RemoveFromTree};

		void PrintLevels(Node* root, int level);
		bool FindNodeByKey(Node** resultParent, Node** resultNode, Key key);
		void AddNodesToList(Node* root, Lab1::List<Node>& list, BypassCode codes[3]) const;
		void Remove(Node* node, Node* parent);
		Node* GetParent(Node* root, Node* node);
		Node* GetPrev(Node* node);
		Node* GetNext(Node* node);
		void CreateFromSortedArray(Node* array, Node* currentNode, int l, int r);
		void BypassNodesWithStack(Node* root, BypassMode mode);


		class Node
		{
		public:
			Node() {};
			Node(Key key, Data value) : key(key), value(value) {};
			Node& operator=(const Node& node) { 
				key = node.key; value = node.value;
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