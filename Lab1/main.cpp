#include <iostream>
#include "list.h"

#define COMMANDS_COUNT 10

using namespace std;

void printCommands(string commands[COMMANDS_COUNT])
{
	for (int i = 0; i < COMMANDS_COUNT; i++)
	{
		cout << i << " - " << commands[i] << " " << endl;
	}
}

int inputValue(string value)
{
	cout << value << ":";
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
		list.Add(inputValue("New element"));
		break;
	case 3:
		cout << "Func returned " << list.Add(inputValue("New element"), inputValue("Index")) << endl;
		break;
	case 4:
	{
		int e;
		try
		{
			e = list[inputValue("Index")];
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
			e = list.GetPos(inputValue("Element"));
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
		cout << "Func returned " << list.RemoveByValue(inputValue("Element")) << endl;
		break;
	case 7:
		cout << "Func returned " << list.RemoveByPos(inputValue("Index")) << endl;
		break;
	case 8:
		cout << "Size: " << list.GetSize() << endl;
		break;
	case 9:
		try
		{
			list[inputValue("Index")] = inputValue("Value");
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}
		break;
	default:
		cout << "Wrong command" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "English");
	string commands[COMMANDS_COUNT] =
	{
		"print list", //0
		"Clear list", //1
		"Add element", //2
		"Add element with index", //3
		"get element by index", //4
		"get index by element", //5
		"remove element by value", //6
		"remove element by index", //7
		"get size of list", //8
		"Set element by index" //9
	};

	Lab1::List<int> list(200);
	Lab1::List<int>::Iterator iterator = list.Begin();
	
	printCommands(commands);

	while (true)
	{
		handleInput(inputValue("Command"), list);
	}
}