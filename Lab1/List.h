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
			Iterator() {}; //конструктор по умолчанию
			Iterator(List<T>& list, int pos); //конструктор с параметрами
			T& operator *(); //возвращает ссылку на элемент списка
			Iterator& operator=(const Iterator& iter) { //оператор присваивания
				list = iter.list; current = iter.current;
				return *this;
			};
			bool operator++(int value); //постфиксный инкремент
			bool operator--(int value); //постфиксный декремент
			bool operator == (Iterator iterator); //операторы сравнения
			bool operator != (Iterator iterator) { return !(*this == iterator); }
		protected:
			List<T>* list = nullptr; //указатель на список
			Node* current = nullptr; //указатель на текущий элемент списка

			friend class List;
		};

		List(): List(1) {} //конструктор по умолчанию
		List(int capacity); //конструктор с параметром
		List(const List<T>&); //конструктор копирования
		~List() { delete array; }; //деструктор
		int GetSize() const { return size; }//возвращает размер списка
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
		int GetReadedElementsCount() const { return readedElements; } //запрос числа элементов списка, просмотренных предыдущей операцией
		void Print(); //вывод списка на экран

	protected:
		int capacity; //ёмкость
		int size = 0; //размер
		int readedElements = 0; //количество просмотренных элементов последней операцией
		int startIndex = NO_INDEX; //индекс первого элемента
		int endIndex = NO_INDEX; //индекс последнего элемента
		int firstFreeIndex = 0; //индекс первого свободного места в массиве
		Node* array; //динамич. массив
		void CreateArrayWithFreeNodes(int capacity); //создание массива со свободными элементами в односвязном списке
		void IncreaseArray(); //увеличение размера массива на 1
		void Remove(Node& node); //удаление элемента
		Node& GetFreeNode(int& index); //возвращает свободный элемент в массиве
		bool FindNodeByPos(int &index, int pos); //поиск элемента по номеру
		bool FindNodeByValue(int &index, int& pos, T value); //поиск элемента по значению
		bool LinkAsPrevAndNext(int index1, int index2);	 //связка элементов как предыдущий и последующий

		class Node
		{
		public:
			Node() { } //конструктор по умолчанию
			Node(const Node& node) : //конструктор копирования
				prevIndex(node.prevIndex), nextIndex(node.nextIndex), value(node.value), index(node.index) {}
			void ResetIndexes() { prevIndex = nextIndex = NO_INDEX; } //сброс индексов
			int prevIndex = NO_INDEX; //индекс предыдущего элемента
			int index = NO_INDEX; //собственный индекс 
			int nextIndex = NO_INDEX; //индекс следующего элемента
			T value; //значение
		};

	};


}
#pragma once 
#include "ListMethods.h"