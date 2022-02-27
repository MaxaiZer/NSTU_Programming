
template <class T>
class List
{
	class Node;

public:
	class Iterator
	{
	public:
		Iterator(List<T>* list, Node* node);
		T& operator *();
		void operator++(int value);
		void operator--(int value);
		bool operator == (Iterator iterator);
		bool operator != (Iterator iterator);
	private:
		List<T>* list;
		Node* cur;
	};

	List() {}; //конструктор
	List(const List<T>&); //конструктор копирования
	~List(); //деструктор
	int getSize() const; //опрос размера списка
	void clear(); //очистка списка
	bool isEmpty() const; //проверка списка на пустоту
	bool contains(T value) const; //опрос наличия заданного значения
	T read(int index) const; //чтение значения с заданным номером в списке
	bool set(T value, int pos); //изменение значения с заданным номером в списке	
	int getPos(T value) const; //получение позиции в списке для заданного значения
	void add(T value); //включение нового значения
	bool add(T value, int pos); //включение нового значения в позицию с заданным номером		
	bool removeByValue(T value); //удаление заданного значения из списка
	bool removeByPos(int pos); //удаление значения из позиции с заданным номером
	Iterator begin(); //запрос прямого итератора begin()
	Iterator end(); //запрос «неустановленного» прямого итератора end()
	void print();

protected:
	int size = 0;
	Node* start = nullptr;
	void remove(Node*);

	class Node
	{
	public:
		Node(T value, Node* prev, Node* next): prev(prev), next(next), value(value) { }
		Node* prev;
		Node* next;
		T value;
	};

};



#pragma once 
#include "ListMethods.h"