#include <iostream>
#include <vector>
#include "BST.h"

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
	cin >> input;
	return input;
}

void handleInput(int input, Lab2::BST<int,int>& bst)
{
	switch (input)
	{
	case 0:
		bst.Print();
		break;
	case 1:
		bst.Clear();
		break;
	case 2:
		cout << "Метод вернул: " << bst.Add(inputValue("Ключ"), inputValue("Значение")) << endl;
		break;
	case 3:
	{
		int e;
		try { e = bst[inputValue("Ключ")]; }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		cout << e << endl;
		break;
	}
	case 4:
		try { bst[inputValue("Ключ")] = inputValue("Значение"); }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		break;
	case 5:
		cout << "Метод вернул: " << bst.Remove(inputValue("Ключ")) << endl;
		break;
	case 6:
		cout << bst.GetSize() << endl;
		break;
	case 7:
		cout << bst.GetReadedElementsCount() << endl;
		break;
	case 8:
	{
		Lab1::List<int> keys = bst.GetKeysList();
		keys.Print();
		break;
	}
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
		"Вывести дерево", //0
		"Очистить дерево", //1
		"Добавить элемент", //2
		"Получить элемент по ключу", //3
		"Изменить элемент по ключу", //4
		"Удалить элемент по ключу", //5
		"Получить размер дерева", //6
		"Количество просмотренных элементов", //7
		"Вывести список ключей (L -> R -> t)" //8
	};

	Lab2::BST<int, int> bst;

	for (int i = 0; i < 1000; i++)
		bst.Add(rand() % 10000, i);

	printCommands(commands);

	while (true)
	{
		handleInput(inputValue("Номер команды"), bst);
	}

}