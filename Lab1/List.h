const int NO_INDEX = -1;

namespace Lab1
{

	template <class T>
	class List
	{
		class Node;

	public:
		class Iterator
		{
		public:
			Iterator(List<T>& list, int index) : list(list) { current = &list.array[index]; }
			T& operator *() { return current->value; }
			bool operator++(int value);
			bool operator--(int value);
			bool operator == (Iterator iterator);
			bool operator != (Iterator iterator);
		private:
			List<T>& list;
			Node* current;

			friend class List;
		};

		List(int capacity); //конструктор
		List(const List<T>&); //конструктор копирования
		~List() { delete array; }; //деструктор
		int GetSize() const { return size; }//опрос размера списка
		void Clear(); //очистка списка
		bool IsEmpty() const { return size == 0; } //проверка списка на пустоту
		bool Contains(T value); //опрос наличия заданного значения
		T& operator[] (const int index); //чтение/изменение значения с заданным номером в списке
		int GetPos(T value); //получение позиции в списке для заданного значения
		bool Add(T value); //включение нового значения
		bool Add(T value, int pos); //включение нового значения в позицию с заданным номером		
		bool RemoveByValue(T value); //удаление заданного значения из списка
		bool RemoveByPos(int pos); //удаление значения из позиции с заданным номером
		Iterator Begin(); //запрос прямого итератора begin()
		Iterator End(); //запрос «неустановленного» прямого итератора end()
		void Print();

	protected:
		int capacity;
		int size = 0;
		int startIndex = NO_INDEX;
		int endIndex = NO_INDEX;
		int firstFreeIndex = 0;
		Node* array;
		void Remove(Node& node);
		Node& GetFreeNode(int& index);
		bool LinkAsPrevAndNext(int index1, int index2);

		class Node
		{
		public:
			Node(const Node& node) :
				prevIndex(node.prevIndex), nextIndex(node.nextIndex), value(node.value), index(index) {}
			Node() { }
			void ResetIndexes() { prevIndex = nextIndex = NO_INDEX; }
			bool operator == (Node node);
			bool operator != (Node node);
			int prevIndex = NO_INDEX;
			int index = NO_INDEX;
			int nextIndex = NO_INDEX;
			T value;
		};

	};


}
#pragma once 
#include "ListMethods.h"