#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "HashTable.h"
#include "TableTest.h"

#define commandView pair<Command, string>

using namespace std;
using namespace Lab4;

enum class Command {
	Print, Clear, Add, GetByKey, ChangeByKey, RemoveByKey, 
	GetSize, GetForm, SwitchToOpenAddr, SwitchToChainsColl,
	TestOpenAddr, TestChainsColl,
	GetTrialsCount, IterSetBegin, IterNext, 
	IterGet, IsIterEnd, PrintCommands, Exit
};

vector<commandView> commandsView = {
{Command::IterSetBegin, "������ ��������: ���������� �� ������ �������"},
{Command::Print, "������� �������"},
{Command::IterNext, "������ ��������: ��������� �������"},
{Command::Clear, "�������� �������"},
{Command::Add, "�������� �������"},
{Command::IterGet, "������ ��������: �������� ��������"},
{Command::GetByKey, "�������� �������� �� �����"},
{Command::IsIterEnd, "������ ��������: ����� �� End()?"},
{Command::RemoveByKey, "������� �������� �� �����"},
{Command::GetSize, "�������� ������ �������"},
{Command::GetTrialsCount, "�������� ���������� ����"},
{Command::PrintCommands, "������� �������"},
{Command::Exit, "�����"},
{Command::SwitchToOpenAddr, "������� ����� �������: �������� ���������"},
{Command::SwitchToChainsColl, "������� ����� �������: ������� ��������"},
{Command::TestOpenAddr, "������������ �������: �������� ���������"},
{Command::TestChainsColl, "������������ �������: ������� ��������"},
{Command::ChangeByKey, "�������� ������� �� �����"},
{Command::GetForm, "����� ����� �������������"}
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

		cout << string(60 - len - commandsView[i].second.length(), ' ');
		printCommand(commandsView[j]);

		cout << endl;
	}

	if (commandsView.size() % 2 != 0)
	{
		printCommand(commandsView.back());
		cout << endl;
	}

}

int inputInt(string hintForUser)
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

string inputString(string hintForUser)
{
	cout << hintForUser << ":";

	string input;

	do
	{
		getline(cin, input);

		for (int i = 0; i < input.length(); i++)
		{
			if ('a' > input[i] || 'z' < input[i])
				goto error;
		}
		break;

	error:
		cout << "Required only small letters of the Latin alphabet" << endl;
		cin.clear();
		cout << hintForUser << ":";
	} while (true);
	
	return input;
}

void handleInput(int input, HashTable<string, int>& table, HashTable<string,int>::Iterator& iter)
{
	switch (input)
	{
	case (int)Command::Print:
		table.Print();
		break;
	case (int)Command::Clear:
		table.Clear();
		break;
	case (int)Command::Add:
		printf("����� ������: %d\n", table.Add(inputString("����"), 1));
		break;
	case (int)Command::GetByKey:
	{
		int e;
		try { e = table[inputString("����")]; }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		cout << e << endl;
		break;
	}
	case (int)Command::ChangeByKey:
		try { table[inputString("����")] =  inputInt("��������"); }
		catch (const char* ex)
		{
			cout << ex << endl;
			break;
		};
		break; 
	case (int)Command::RemoveByKey:
		printf("����� ������: %d\n", table.Remove(inputString("����")));
		break;
	case (int)Command::GetSize:
		cout << table.GetSize() << endl;
		break;
	case (int)Command::GetTrialsCount:
		cout << table.GetTrialsCount() << endl;
		break;
	case (int)Command::IterSetBegin:
		iter = table.Begin();
		break;
	case (int)Command::IterNext:
		cout << "����� ������: " << iter++ << endl;
		break;
	case (int)Command::IterGet:
		try { cout << *iter << endl; }
		catch (const char* ex) { cout << ex << endl; }
		break;
	case (int)Command::IsIterEnd:
		cout << (iter == table.End()) << endl;
		break;
	case (int)Command::SwitchToOpenAddr:
		table.SetForm(FormName::OpenAddressing);
		break;
	case (int)Command::SwitchToChainsColl:
		table.SetForm(FormName::ChainsOfCollisions);
		break;
	case (int)Command::TestOpenAddr:
	{
		int keysCount = inputInt("���������� ������");
		testOpenAddr(keysCount);
		break;
	}
	case (int)Command::TestChainsColl:
	{
		int keysCount = inputInt("���������� ������");
		testChainsColl(keysCount);
		break;
	}
	case (int)Command::GetForm:
		if (table.GetForm() == FormName::OpenAddressing)
			cout << "�������� ���������" << endl;
		else
			cout << "� ��������� ��������" << endl;
		break;
	case (int)Command::PrintCommands:
		system("CLS");
		printCommands();
		break;
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

	HashTable<string, int> table(10);
	HashTable<string, int>::Iterator iter;

	printCommands();

	while (true)
	{
		handleInput(inputInt("����� �������"), table, iter);
	}
}