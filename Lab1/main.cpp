#include <iostream>
#include "list.h"

#define COMMANDS_COUNT 11

using namespace std;

void printCommands(string commands[COMMANDS_COUNT])
{
	for (int i = 0; i < COMMANDS_COUNT; i++)
	{
		cout << i << " - " << commands[i] << " " << endl;
	}
}

int inputValue(string hintForUser)
{
	cout << hintForUser << ":";
	int input;
	cin >> input;
	return input;
}

void handleInput(int input, Lab1::List<int>& list)
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
		cout << "Функция вернула " << list.Add(inputValue("Значение")) << endl;
		break;
	case 3:
		cout << "Функция вернула " << list.Add(inputValue("Значение"), inputValue("Индекс")) << endl;
		break;
	case 4:
	{
		int e;
		try 
		{ 
			e = list[inputValue("Индекс")]; 
		}
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
		try
		{
			e = list.GetPos(inputValue("Значение"));
		}
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		cout << e << endl;
		break;
	}
	case 6:
		cout << "Функция вернула " << list.RemoveByValue(inputValue("Значение")) << endl;
		break;
	case 7:
		cout << "Функция вернула " << list.RemoveByPos(inputValue("Индекс")) << endl;
		break;
	case 8:
		cout << "Размер: " << list.GetSize() << endl;
		break;
	case 9:
		try
		{
			list[inputValue("Индекс")] = inputValue("Значение");
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}
		break;
	case 10:
		cout << "Функция вернула " << list.ChangeCapacity(inputValue("Новая ёмкость")) << endl;
		break;
	default:
		cout << "Неправильный номер команды" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string commands[COMMANDS_COUNT] =
	{
		"Вывести список", //0
		"Очистить список", //1
		"Добавить элемент", //2
		"Добавить элемент с индексом", //3
		"Получить элемент по индексу", //4
		"Получить индекс по элементу", //5
		"Удалить элемент по значению", //6
		"Удалить элемент по индексу", //7
		"Получить размер списка", //8
		"Изменить элемент по индексу", //9
		"Изменить ёмкость" //10
	};

	Lab1::List<int> list(20);
	Lab1::List<int>::Iterator iterator = list.Begin();
	
	printCommands(commands);

	while (true)
	{
		handleInput(inputValue("Номер команды"), list);
	}
}