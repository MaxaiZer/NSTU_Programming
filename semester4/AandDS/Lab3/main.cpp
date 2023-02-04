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
{Command::Fulfill, "��������� ������ ��� �����"},
{Command::IterSetBegin, "������ ��������: ���������� �� ������ ������"},
{Command::Print, "������� ������"},
{Command::IterNext, "������ ��������: ��������� �������"},
{Command::Clear, "�������� ������"},
{Command::IterPrev, "������ ��������: ���������� �������"},
{Command::Add, "�������� �������"},
{Command::IterGet, "������ ��������: �������� ��������"},
{Command::GetByKey, "�������� ������� �� �����"},
{Command::ChangeByKey, "�������� ������� �� �����"},
{Command::IsIterEnd, "������ ��������: ����� �� End()?"},
{Command::RemoveByKey, "������� ������� �� �����"},
{Command::RIterSetRBegin, "�������� ��������: ���������� �� ����� ������"},
{Command::GetSize, "�������� ������ ������"},
{Command::RIterNext, "�������� ��������: ��������� �������"},
{Command::GetReadElemsCount, "���������� ������������� ���������"},
{Command::RIterPrev, "�������� ��������: ���������� �������"},
{Command::RIterGet, "�������� ��������: �������� ��������"},
{Command::TestRandomTree, "���� ����������� ���������� ������"},
{Command::IsRIterRend, "�������� ��������: ����� �� Rend()?"},
{Command::TestOrdinaryTree, "���� ����������� ������������ ������"},
{Command::PrintCommands, "������� �������"},
{Command::Exit, "�����"}
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
		cin.clear(); //���������� ��, ����� ����
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
		cout << "����� ������: " << bst.Add(inputValue("����"), inputValue("��������")) << endl;
		break;
	case (int)Command::GetByKey:
	{
		int e;
		try { e = bst.Get(inputValue("����")); }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		cout << e << endl;
		break;
	}
	case (int)Command::ChangeByKey:
		try { bst.Set(inputValue("����"), inputValue("��������")); }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		break;
	case (int)Command::RemoveByKey:
		cout << "����� ������: " << bst.Remove(inputValue("����")) << endl;
		break;
	case (int)Command::GetSize:
		cout << bst.GetSize() << endl;
		break;
	case (int)Command::GetReadElemsCount:
		cout << bst.GetReadElementsCount() << endl;
		break;
	case (int)Command::TestRandomTree:
		testRandomTree(inputValue("������ ������������ ������"));
		break;
	case (int)Command::TestOrdinaryTree:
		testOrdinaryTree(inputValue("������ ������������ ������"));
		break;
	case (int)Command::IterSetBegin:
		iters.forward = bst.Begin();
		break;
	case (int)Command::IterNext:
		cout << "����� ������: " << iters.forward++ << endl;
		break;
	case (int)Command::IterPrev:
		cout << "����� ������: " << iters.forward-- << endl;
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
		cout << "����� ������: " << iters.reverse++ << endl;
		break;
	case (int)Command::RIterPrev:
		cout << "����� ������: " << iters.reverse-- << endl;
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
		int size = inputValue("������");
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
		cout << "������������ ����� �������" << endl;
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
		handleInput(inputValue("����� �������"), bst, iters);
	}
}