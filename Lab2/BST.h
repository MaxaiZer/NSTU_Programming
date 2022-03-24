#include "../Lab1/List.h"

namespace Lab2
{
	#define IterNotInstalledEx "Iterator is not installed"

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
			Data& operator *() const //возвращает ссылку на значение текущего узла
			{
				if (current != nullptr)
					return current->value;

				throw IterNotInstalledEx;
			}
			bool operator++(int value) //переход к следующему узлу при прямом обходе
			{ return (current = bst->GetNext(current)) != nullptr; }	
			bool operator--(int value)  //переход к предыдущему узлу при прямом обходе
			{ return (current = bst->GetPrev(current)) != nullptr; }
			bool operator == (Iterator iter) const { return bst == iter.bst && current == iter.current; }
			bool operator != (Iterator iter) const { return !(*this == iter); }
		protected:
			BST* bst = nullptr; //указатель на дерево
			Node* current = nullptr; //указатель на текущий узел дерева

			friend class BST;
		};

		class ReverseIterator
		{
		public:
			ReverseIterator() {};
			ReverseIterator(BST& bst, Node* node) { this->bst = &bst; current = node; }
			Data& operator *() const 
			{
				if (current != nullptr)
					return current->value;
				
				throw IterNotInstalledEx;
			}
			bool operator++(int value) //переход к предыдущему узлу при прямом обходе
			{ return (current = bst->GetPrev(current)) != nullptr; }
			bool operator--(int value) // переход к следующему узлу при прямом обходе
			{ return (current = bst->GetNext(current)) != nullptr;}
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
		Data& operator[] (Key key); //чтение/изменение значения с заданным ключом
		bool Add(Key key, Data value); 
		bool Remove(Key key); 
		Lab1::List<Key> GetKeysList() const; //возвращает список ключей по схеме L -> R -> t
		int GetReadedElementsCount() const { return readedElements; } //опрос числа узлов дерева, просмотренных предыдущей операцией
		void Print() const;
		void MergeWith(const BST<Key,Data>& bst);  //объединение с другим деревом

		Iterator Begin(); //запрос прямого итератора, установленного на узел дерева с минимальным ключом
		Iterator End() { return Iterator(*this, nullptr); } //запрос «неустановленного» прямого итератора
		ReverseIterator Rbegin(); //запрос обратного итератора, установленного на узел дерева с максимальным ключом
		ReverseIterator Rend() { return ReverseIterator(*this, nullptr); } //запрос «неустановленного» обратного итератора
	protected:
		int size = 0;
		mutable int readedElements = 0; //число узлов дерева, просмотренных предыдущей операцией
		Node* root = nullptr;

		enum class BypassCode { L, T, R }; //для составления схемы обхода
		void AddNodesToList(Node* root, Lab1::List<Node>& list, BypassCode codes[3]) const; //добавление узлов в список по схеме обхода

		enum class BypassMode {AddToTree, DeleteFromMemory}; //режим обхода дерева
		void BypassTree(Node* root, BypassMode mode); //обход дерева, где для каждого узла выполняется действие согласно режиму обхода

		void PrintLevels(Node* root, int level) const; //рекурсивный вывод дерева
		bool FindNodeByKey(Node** resultParent, Node** resultNode, Key key) const;
		void Remove(Node* node, Node* parent); 
		Node* GetParent(Node* node) const;
		Node* GetPrev(Node* node) const; //следующий узел при прямом обходе
		Node* GetNext(Node* node) const; //предыдущий узел при прямом обходе
		void CreateFromSortedArray(Node* array, Node* currentNode, int l, int r); //создание дерева из отсортированного по ключам списка узлов

		class Node
		{
		public:
			Key key;
			Data value;
			Node* left = nullptr;
			Node* right = nullptr;

			Node() {};
			Node(Key key, Data value) : key(key), value(value) {};

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