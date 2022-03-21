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
			Data& operator *() const;
			bool operator++(int value);
			bool operator--(int value);
			bool operator == (Iterator iter) const { return bst == iter.bst && current == iter.current; }
			bool operator != (Iterator iter) const { return !(*this == iter); }
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
			Data& operator *() const;
			bool operator++(int value);
			bool operator--(int value);
			bool operator == (ReverseIterator iter) const { return bst == iter.bst && current == iter.current; }
			bool operator != (ReverseIterator iter) const { return !(*this == iter); }
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
		void Print() const;
		void MergeWith(const BST<Key,Data>& bst);

		Iterator Begin();
		Iterator End() { return Iterator(*this, nullptr); }
		ReverseIterator Rbegin();
		ReverseIterator Rend() { return ReverseIterator(*this, nullptr); }
	protected:
		int size = 0;
		mutable int readedElements = 0;
		Node* root = nullptr;

		const enum BypassCode { L, T, R };
		void AddNodesToList(Node* root, Lab1::List<Node>& list, BypassCode codes[3]) const;

		const enum BypassMode {AddToTree, RemoveFromTree};
		void BypassNodesWithStack(Node* root, BypassMode mode);

		void PrintLevels(Node* root, int level) const;
		bool FindNodeByKey(Node** resultParent, Node** resultNode, Key key) const;
		void Remove(Node* node, Node* parent);
		Node* GetParent(Node* root, Node* node) const;
		Node* GetPrev(Node* node) const;
		Node* GetNext(Node* node) const;
		void CreateFromSortedArray(Node* array, Node* currentNode, int l, int r);

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
			Node* GetMaxInChild() const {
				if (this->right == nullptr)
					return nullptr;

				Node* max = this->right;
				while (max->right != nullptr)
					max = max->right;

				return max;
			}
			Node* GetMinInChild() const {
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