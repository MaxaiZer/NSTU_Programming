#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include "BST.h"
#include "TreeTest.h"

#define commandView pair<Command, const char*>

using namespace std;
using namespace Lab2;

enum class Command { Fulfill, Print, Clear,  Add, GetByKey, ChangeByKey,
					RemoveByKey, GetSize, GetReadElemsCount, 
					GetKeys, Merge, TestRandomTree, TestOrdinaryTree,
					IterSetBegin, IterNext, IterPrev, IterGet, IsIterEnd,
					RIterSetRBegin, RIterNext, RIterPrev, RIterGet, IsRIterRend, PrintCommands, Exit};

vector<pair<Command, const char*>> commandsView = { 
{Command::Fulfill, "Заполнить дерево для теста"},
{Command::IterSetBegin, "Прямой итератор: установить на начало дерева"},
{Command::Print, "Вывести дерево"},
{Command::IterNext, "Прямой итератор: следующий элемент"},
{Command::Clear, "Очистить дерево"},
{Command::IterPrev, "Прямой итератор: предыдущий элемент"},
{Command::Add, "Добавить элемент"},
{Command::IterGet, "Прямой итератор: получить значение"},
{Command::GetByKey, "Получить элемент по ключу"},
{Command::ChangeByKey, "Изменить элемент по ключу"},
{Command::IsIterEnd, "Прямой итератор: равен ли End()?"},
{Command::RemoveByKey, "Удалить элемент по ключу"},
{Command::RIterSetRBegin, "Обратный итератор: установить на конец дерева"},
{Command::GetSize, "Получить размер дерева"},
{Command::RIterNext, "Обратный итератор: следующий элемент"},
{Command::GetReadElemsCount, "Количество просмотренных элементов"},
{Command::RIterPrev, "Обратный итератор: предыдущий элемент"},
{Command::GetKeys, "Вывести список ключей (L -> R -> t)"},
{Command::RIterGet, "Обратный итератор: получить значение"},
{Command::TestRandomTree, "Тест трудоёмкости случайного дерева"},
{Command::IsRIterRend, "Обратный итератор: равен ли Rend()?"},
{Command::TestOrdinaryTree, "Тест трудоёмкости вырожденного дерева"},
{Command::PrintCommands, "Вывести команды"},
{Command::Exit, "Выход"},
{Command::Merge, "Объединить с другим деревом"}
};

void printCommands()
{
	auto printCommand = [](commandView view)
	{ 
		cout << (int)view.first << " - " << view.second; 
	};

	for (int i = 0, j = commandsView.size() / 2; i < commandsView.size() / 2; i++, j++)
	{
		printCommand(commandsView[i]);

		int k = (int)commandsView[i].first / 10;
		int len = 1;
		
		while (k != 0)
		{
			len++; k /= 10;
		}

		cout << string(60 - len - strlen(commandsView[i].second), ' ');
		printCommand(commandsView[j]);

		cout << endl;
	}

	if (commandsView.size() % 2 != 0)
	{
		printCommand(commandsView.back());
		cout << endl;
	}

}

int inputValue(string hintForUser)
{
	cout << hintForUser << ":";
	int input;
	cin.clear(); 
	while (!(cin >> input))
	{
		cin.clear(); //игнорируем всё, кроме цифр
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Only numbers are required" << endl;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return input;
}

struct Iterators
{
	Lab2::BST<int, int>::Iterator forward;
	Lab2::BST<int, int>::ReverseIterator reverse;
};

void handleInput(int input, Lab2::BST<int,int>& bst, Iterators& iters)
{
	switch (input)
	{
	case (int)Command::Print:
		bst.Print();
		break;
	case (int)Command::Clear:
		bst.Clear();
		break;
	case (int)Command::Add:
		cout << "Метод вернул: " << bst.Add(inputValue("Ключ"), inputValue("Значение")) << endl;
		break;
	case (int)Command::GetByKey:
	{
		int e;
		try { e = bst.Get(inputValue("Ключ")); }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		cout << e << endl;
		break;
	}
	case (int)Command::ChangeByKey:
		try { bst.Set(inputValue("Ключ"),inputValue("Значение")); }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		break;
	case (int)Command::RemoveByKey:
		cout << "Метод вернул: " << bst.Remove(inputValue("Ключ")) << endl;
		break;
	case (int)Command::GetSize:
		cout << bst.GetSize() << endl;
		break;
	case (int)Command::GetReadElemsCount:
		cout << bst.GetReadElementsCount() << endl;
		break;
	case (int)Command::GetKeys:
	{
		std::list<int> keys = bst.GetKeysList();

		if (keys.empty())
			cout << "List is empty";

		for (auto it = keys.begin(); it != keys.end(); it++)
			cout << *it << " ";

		cout << endl;
		break;
	}
	case (int)Command::TestRandomTree:
		testRandomTree(inputValue("Размер тестируемого дерева"));
		break;
	case (int)Command::TestOrdinaryTree:
		testOrdinaryTree(inputValue("Размер тестируемого дерева"));
		break;
		case (int)Command::IterSetBegin:
		iters.forward = bst.Begin();
		break;
	case (int)Command::IterNext:
		cout << "Метод вернул: " << iters.forward++ << endl;
		break;
	case (int)Command::IterPrev:
		cout << "Метод вернул: " << iters.forward-- << endl;
		break;
	case (int)Command::IterGet:
		try { cout << *iters.forward << endl; }
		catch (const char* ex) { cout << ex << endl; }
		break;
	case (int)Command::IsIterEnd:
		cout << (iters.forward == bst.End()) << endl;
		break;
	case (int)Command::RIterSetRBegin:
		iters.reverse = bst.Rbegin();
		break;
	case (int)Command::RIterNext:
		cout << "Метод вернул: " << iters.reverse++ << endl;
		break;
	case (int)Command::RIterPrev:
		cout << "Метод вернул: " << iters.reverse-- << endl;
		break;
	case (int)Command::RIterGet:
		try { cout << *iters.reverse << endl; }
		catch (const char* ex) { cout << ex << endl; }
		break;
	case (int)Command::IsRIterRend:
		cout << (iters.reverse == bst.Rend()) << endl;
		break;
	case (int)Command::PrintCommands:
		system("CLS");
		printCommands();
		break;
	case(int)Command::Fulfill:
	{
		int size = inputValue("Размер");
		if (size < 1)
		{
			cout << "Wrong size" << endl;
			return;
		}

		bst.Clear();

		BST<int, int> another;
		for (int i = 1; i <= size; i++)
		{
			bst.Add(i, i);
			another.Add(i, i);
		}

		bst.MergeWith(another);
		break;
	}
	case(int)Command::Exit:
	{
		exit(0);
		break;
	}
	case (int)Command::Merge:
	{
		int size = inputValue("Размер второго дерева");
		if (size < 1)
		{
			cout << "Wrong size" << endl;
			return;
		}
		BST<int, int> bst2;

		for (int i = 0; i < size; i++)
			bst2.Add(inputValue("Ключ " + to_string(i+1)), 1);

		bst.MergeWith(bst2);
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

	auto sortCommands = [](commandView p1, commandView p2)
	{
		return (int)p1.first < (int)p2.first;
	};
	sort(commandsView.begin(), commandsView.end(), sortCommands);

	Lab2::BST<int, int> bst;
	Iterators iters;

	printCommands();
	
	while (true)
	{
		handleInput(inputValue("Номер команды"), bst, iters);
	}
}