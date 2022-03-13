#include <iostream>
#include <vector>
#include "list.h"

const int ITERATORS_COUNT = 2;

using namespace std;

void printCommands(vector<string> commands)
{
	for (int i = 0; i < commands.size(); i++)
	{
		cout << i << " - " << commands[i] << endl;
	}
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

int inputIterNumber()
{
	int number = inputValue("Номер итератора");
	while (0 > number || number >= ITERATORS_COUNT)
	{
		cout << "Неправильный номер" << endl;
		number = inputValue("Номер итератора");
	}
	return number;
}

void handleInput(int input, Lab1::List<int>& list, Lab1::List<int>::Iterator iters[ITERATORS_COUNT])
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
		cout << list.GetReadedElementsCount() << endl;
		break;
	case 11:
		iters[inputIterNumber()] = list.Begin();
		break;
	case 12:
		cout << "Метод вернул " << iters[inputIterNumber()]++ << endl;
		break;
	case 13:
		cout << "Метод вернул " << iters[inputIterNumber()]-- << endl;
		break;
	case 14:
		try { cout << *iters[inputIterNumber()] << endl; }
		catch (const char* ex)
		{
			cout << ex << endl;
		}
		break;
	case 15:
		cout << (iters[0] == iters[1]) << endl;
		break;
	case 16:
		cout << (iters[inputIterNumber()] == list.End()) << endl;
		break;
	default:
		cout << "Неправильный номер команды" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<string> commands =
	{ 
		"Вывести список", //0
		"Очистить список", //1
		"Добавить элемент", //2
		"Добавить элемент с номером", //3
		"Получить элемент по номеру", //4
		"Получить номер по элементу", //5
		"Удалить элемент по значению", //6
		"Удалить элемент по номеру", //7
		"Получить размер списка", //8
		"Изменить элемент по номеру", //9
		"Количество просмотренных элементов", //10
		"Установить итератор на начало списка", //11
		"Итератор: следующее значение", // 12
		"Итератор: предыдущее значение", //13
		"Разыменовать итератор", //14
		"Равны ли итераторы?", //15
		"Равен ли итератор End()?" //16
	};

	Lab1::List<int> list;
	Lab1::List<int>::Iterator iterators[ITERATORS_COUNT];

	printCommands(commands);

	while (true)
	{
		handleInput(inputValue("Номер команды"), list, iterators);
	}

}