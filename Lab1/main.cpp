#include <iostream>
#include "list.h"

using namespace std;

void printCommands()
{
	cout << "0 - Вывести список" << endl;
	cout << "1 - Очистить список" << endl;
	cout << "2 - Добавить элемент" << endl;
	cout << "3 - Добавить элемент с номером" << endl;
	cout << "4 - Получить элемент по номеру" << endl;
	cout << "5 - Получить номер по элементу" << endl;
	cout << "6 - Удалить элемент по значению" << endl;
	cout << "7 - Удалить элемент по номеру" << endl;
	cout << "8 - Получить размер списка" << endl;
	cout << "9 - Изменить элемент по номеру" << endl;
	cout << "10 - Количество просмотренных элементов" << endl;
	cout << "11 - Установить итератор на начало списка" << endl;
	cout << "12 - Итератор: следующее значение" << endl;
	cout << "13 - Итератор: предыдущее значение" << endl;
	cout << "14 - Получить значение по итератору" << endl;
	cout << "15 - Равен ли итератор End()?" << endl;
	cout << "16 - Вывод команд" << endl;
}

int inputValue(string hintForUser)
{
	cout << hintForUser << ":";
	int input;
	while (!(cin >> input))
	{
		cin.clear(); //игнорируем всё, кроме цифр
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return input;
}

void handleInput(int input, Lab1::List<int>& list, Lab1::List<int>::Iterator& iter)
{
	switch (input)
	{
	case 0:
		list.Print();
		break;
	case 1:
		list.Clear();
		break;
	case 2:
		list.Add(inputValue("Значение"));
		break;
	case 3:
		cout << "Метод вернул " << list.Add(inputValue("Значение"), inputValue("Номер")) << endl;
		break;
	case 4:
	{
		int e;
		try { e = list[inputValue("Номер")];  }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		cout << e << endl;
		break;
	}
	case 5:
	{
		int e;
		try { e = list.GetPos(inputValue("Значение")); }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		cout << e << endl;
		break;
	}
	case 6:
		cout << "Метод вернул " << list.RemoveByValue(inputValue("Значение")) << endl;
		break;
	case 7:
		cout << "Метод вернул " << list.RemoveByPos(inputValue("Номер")) << endl;
		break;
	case 8:
		cout << "Размер: " << list.GetSize() << endl;
		break;
	case 9:
		try { list[inputValue("Номер")] = inputValue("Значение"); }
		catch (const char* ex)
		{
			cout << ex << endl;
		}
		break;
	case 10:
		cout << list.GetReadElementsCount() << endl;
		break;
	case 11:
		iter = list.Begin();
		break;
	case 12:
		cout << "Метод вернул " << iter++ << endl;
		break;
	case 13:
		cout << "Метод вернул " << iter-- << endl;
		break;
	case 14:
		try { cout << *iter << endl; }
		catch (const char* ex)
		{
			cout << ex << endl;
		}
		break;
	case 15:
		cout << (iter == list.End()) << endl;
		break;
	case 16:
		system("CLS");
		printCommands();
		break;
	default:
		cout << "Неправильный номер команды" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Lab1::List<int> list;
	Lab1::List<int>::Iterator iterator;

	printCommands();

	while (true)
	{
		handleInput(inputValue("Номер команды"), list, iterator);
	}

}