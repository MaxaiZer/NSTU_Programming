namespace Lab1
{

	const int NO_INDEX = -1; //значение, если индекса не существует

	template <class T>
	class List
	{
		class Node;

	public:
		class Iterator
		{
		public:
			Iterator() {}; 
			Iterator(List<T>& list, int pos);
			T& operator *() const; //возвращает ссылку на значение текущего элемента
			Iterator& operator=(const Iterator& iter) {
				list = iter.list; current = iter.current;
				return *this;
			};
			bool operator++(int value); //переход к следующему элементу
			bool operator--(int value); //переход к предыдущему элементу
			bool operator == (Iterator iterator) const; 
			bool operator != (Iterator iterator) const { return !(*this == iterator); }
		protected:
			List<T>* list = nullptr; //указатель на список
			Node* current = nullptr; //указатель на текущий элемент списка

			friend class List;
		};

		List(): List(1) {} 
		List(int capacity); 
		List(const List<T>&);
		~List() { delete[] array; }; 
		int GetSize() const { return size; }
		void Clear(); 
		bool IsEmpty() const { return size == 0; } 
		bool Contains(T value) const; 
		T& operator[] (int pos); //чтение/изменение значения с заданным номером в списке
		int GetPos(T value) const; 
		void Add(T value);
		bool Add(T value, int pos); 
		bool RemoveByValue(T value); 
		bool RemoveByPos(int pos); 
		Iterator Begin(); //запрос прямого итератора
		Iterator End(); //запрос «неустановленного» прямого итератора
		int GetReadedElementsCount() const { return readedElements; } //запрос числа элементов, просмотренных последней операцией
		void Print(); 

	protected:
		int capacity;
		int size = 0; 
		mutable int readedElements = 0; //количество просмотренных элементов последней операцией
		int startIndex = NO_INDEX; //индекс первого элемента
		int endIndex = NO_INDEX; //индекс последнего элемента
		int firstFreeIndex = NO_INDEX; //первый свободный индекс в массиве
		Node* array = nullptr; //динамич. массив элементов

		void CreateArrayWithFreeNodes(int capacity); //создание массива со свободными элементами в односвязном списке
		void IncreaseArray(); //увеличение размера массива на 1
		void Remove(Node& node); 
		Node& GetFreeNode(int& index); //возвращает свободный элемент в массиве
		bool FindNodeByPos(int &index, int pos) const;
		bool FindNodeByValue(int &index, int& pos, T value) const;
		bool LinkAsPrevAndNext(int index1, int index2);	 //связка элементов как предыдущий и последующий

		class Node
		{
		public:
			int prevIndex = NO_INDEX; //индекс предыдущего элемента
			int index = NO_INDEX; //собственный индекс 
			int nextIndex = NO_INDEX; //индекс следующего элемента
			T value;

			Node() { } 
			void ResetIndexes() { prevIndex = nextIndex = NO_INDEX; } //сброс индексов
		};

	};


}
#pragma once 
#include "ListMethods.h"