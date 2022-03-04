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
			List<T>* list;
			Node* current = nullptr;
			bool isInstalled = false;

			friend class List;
		};

		List(): List(1) {} //конструктор по умолчанию
		List(int capacity); //конструктор с параметром
		List(const List<T>&); //конструктор копирования
		~List() { delete array; }; //деструктор
		int GetSize() const { return size; }//опрос размера списка
		void Clear(); //очистка списка
		bool IsEmpty() const { return size == 0; } //проверка списка на пустоту
		bool Contains(T value); //опрос наличия заданного значения
		T& operator[] (int index); //чтение/изменение значения с заданным номером в списке
		int GetPos(T value); //получение позиции в списке для заданного значения
		void Add(T value); //включение нового значения
		bool Add(T value, int pos); //включение нового значения в позицию с заданным номером		
		bool RemoveByValue(T value); //удаление заданного значения из списка
		bool RemoveByPos(int pos); //удаление значения из позиции с заданным номером
		Iterator Begin(); //запрос прямого итератора begin()
		Iterator End(); //запрос «неустановленного» прямого итератора end()
		int GetReadedElemetsCount() const { return readedElements; } //запрос числа элементов списка, просмотренных предыдущей операцией
		void Print(); //вывод списка на экран

	protected:
		int capacity;
		int size = 0;
		int readedElements = 0;
		int startIndex = NO_INDEX;
		int endIndex = NO_INDEX;
		int firstFreeIndex = 0;
		Node* array;
		void CreateArrayWithFreeNodes(int capacity);
		void Remove(Node& node);
		Node& GetFreeNode(int& index);
		bool FindNodeByPos(int &index, int pos);
		bool FindNodeByValue(int &index, int& pos, T value);
		bool LinkAsPrevAndNext(int index1, int index2);
		void IncreaseArray();

		class Node
		{
		public:
			Node(const Node& node) :
				prevIndex(node.prevIndex), nextIndex(node.nextIndex), value(node.value), index(node.index) {}
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