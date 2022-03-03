namespace Lab1
{

	const int NO_INDEX = -1;

	template <class T>
	class List
	{
		class Node;

	public:
		class Iterator
		{
		public:
			Iterator(List<T>& list, int pos);
			T& operator *();
			Iterator& operator=(const Iterator& iter) {
				list = iter.list; current = iter.current; isInstalled = iter.isInstalled;
				return *this;
			};
			bool operator++(int value);
			bool operator--(int value);
			bool operator == (Iterator iterator);
			bool operator != (Iterator iterator);
		private:
			List<T>& list;
			Node* current = nullptr;
			bool isInstalled = false;

			friend class List;
		};

		List(int capacity); //конструктор
		List(const List<T>&); //конструктор копирования
		~List() { delete array; }; //деструктор
		int GetSize() const { return size; }//опрос размера списка
		bool ChangeCapacity(int newCapacity);
		void Clear(); //очистка списка
		bool IsEmpty() const { return size == 0; } //проверка списка на пустоту
		bool Contains(T value) const; //опрос наличия заданного значения
		T& operator[] (const int index); //чтение/изменение значения с заданным номером в списке
		int GetPos(T value) const; //получение позиции в списке для заданного значения
		bool Add(T value); //включение нового значения
		bool Add(T value, int pos); //включение нового значения в позицию с заданным номером		
		bool RemoveByValue(T value); //удаление заданного значения из списка
		bool RemoveByPos(int pos); //удаление значения из позиции с заданным номером
		Iterator Begin(); //запрос прямого итератора begin()
		Iterator End(); //запрос «неустановленного» прямого итератора end()
		void Print();
		//void PrintArray(); //отладка

	protected:
		int capacity;
		int size = 0;
		int startIndex = NO_INDEX;
		int endIndex = NO_INDEX;
		int firstFreeIndex = 0;
		Node* array;
		void InitializeArray(Node* nodes, int size);
		void Remove(Node& node);
		Node& GetFreeNode(int& index);
		bool FindNodeByPos(int &index, int pos) const;
		bool FindNodeByValue(int &index, int& pos, T value) const;
		bool LinkAsPrevAndNext(int index1, int index2);

		class Node
		{
		public:
			Node(const Node& node) :
				prevIndex(node.prevIndex), nextIndex(node.nextIndex), value(node.value), index(index) {}
			Node() { }
			void ResetIndexes() { prevIndex = nextIndex = NO_INDEX; }
			int prevIndex = NO_INDEX;
			int index = NO_INDEX;
			int nextIndex = NO_INDEX;
			T value;
		};

	};


}
#pragma once 
#include "ListMethods.h"