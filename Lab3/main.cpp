#include <iostream>
#include <string>
#include <vector>
#include "TreeTest.h"
#include "Tree23.h"

#define commandView pair<Command, const char*>

using namespace std;
using namespace Lab3;

enum class Command {
	Fulfill, Print, Clear, Add, GetByKey, ChangeByKey,
	RemoveByKey, GetSize, GetReadElemsCount,
	TestRandomTree, TestOrdinaryTree,
	IterSetBegin, IterNext, IterPrev, IterGet, IsIterEnd,
	RIterSetRBegin, RIterNext, RIterPrev, RIterGet, IsRIterRend, PrintCommands, Exit
};

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
{Command::RIterGet, "Обратный итератор: получить значение"},
{Command::TestRandomTree, "Тест трудоёмкости случайного дерева"},
{Command::IsRIterRend, "Обратный итератор: равен ли Rend()?"},
{Command::TestOrdinaryTree, "Тест трудоёмкости вырожденного дерева"},
{Command::PrintCommands, "Вывести команды"},
{Command::Exit, "Выход"}
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

		for (int s = strlen(commandsView[i].second); s < 60 - len; s++)
			cout << " ";

		if (j < commandsView.size())
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
	Tree23<int, int>::Iterator forward;
	Tree23<int, int>::ReverseIterator reverse;
};

void handleInput(int input, Tree23<int, int>& bst, Iterators& iters)
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
		try { bst.Set(inputValue("Ключ"), inputValue("Значение")); }
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


		for (int i = 1; i <= size; i++)
			bst.Add(i, i);

		break;
	}
	case(int)Command::Exit:
	{
		exit(0);
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

	Tree23<int, int> bst;
	Iterators iters;

	printCommands();

	while (true)
	{
		handleInput(inputValue("Номер команды"), bst, iters);
	}
}