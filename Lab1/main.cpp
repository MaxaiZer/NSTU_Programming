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

void handleInput(int input, List<int>& list)
{
	switch (input)
	{
	case 0:
		list.print();
		break;
	case 1:
		list.clear();
		break;
	case 2:
		list.add(inputValue("New element"));
		break;
	case 3:
		cout << "Func returned " << list.add(inputValue("New element"), inputValue("Index")) << endl;
		break;
	case 4:
	{
		int e;
		try
		{
			e = list.read(inputValue("Index"));
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
			e = list.getPos(inputValue("Element"));
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
		cout << "Func returned " << list.removeByValue(inputValue("Element")) << endl;
		break;
	case 7:
		cout << "Func returned " << list.removeByPos(inputValue("Index")) << endl;
		break;
	case 8:
		cout << "Size: " << list.getSize() << endl;
		break;
	case 9:
		cout << "Func returned " << list.set(inputValue("Element"), inputValue("Index")) << endl;
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
		"clear list", //1
		"add element", //2
		"add element with index", //3
		"get element by index", //4
		"get index by element", //5
		"remove element by value", //6
		"remove element by index", //7
		"get size of list", //8
		"set element by index" //9
	};

	List<int> list;
	List<int>::Iterator iterator = list.begin();
	
	printCommands(commands);

	while (true)
	{
		handleInput(inputValue("Command"), list);
	}
}