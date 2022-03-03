#include <iostream>
#include <vector>
#include "list.h"

using namespace std;

void printCommands(vector<string> commands)
{
	int index = 0;
	
	for (int i = 0; i < commands.size(); i++)
	{
		cout << i << " - " << commands[i] << endl;
	}
}

int inputValue(string hintForUser)
{
	cout << hintForUser << ":";
	int input;
	cin >> input;
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
		try { list[inputValue("Индекс")] = inputValue("Значение"); }
		catch (const char* ex)
		{
			cout << ex << endl;
		}
		break;
	case 10:
		cout << list.GetReadedElemetsCount() << endl;
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
		"Получить индекс по элементу", //5
		"Удалить элемент по значению", //6
		"Удалить элемент по номеру", //7
		"Получить размер списка", //8
		"Изменить элемент по номеру", //9
		"Количество просмотренных элементов", //10
		"Установить итератор на начало списка", //11
		"Итератор: следующее значение", // 12
		"Итератор: предыдущее значение", //13
		"Разыменовать итератор", //14
		"Равен ли итератор End()?" //15
	};

	Lab1::List<int> list;
	Lab1::List<int>::Iterator iter = list.Begin();

	printCommands(commands);

	while (true)
	{
		handleInput(inputValue("Номер команды"), list, iter);
	}

}