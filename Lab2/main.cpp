#include <iostream>
#include <vector>
#include "BST.h"

using namespace std;
typedef unsigned long long INT_64;

static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

void setFirstRandomDigit() { srand(time(0)); RRand = (INT_64)rand(); }

//линейный конгруэнтный генератор Xi+1=(a*Xi+c)%m
INT_64 lineRand()
{
	INT_64 y1, y2;
	y1 = (aRand * RRand + cRand) % mRand;
	y2 = (aRand * y1 + cRand) % mRand;
	RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 &
		0xFFFFFFFF00000000LL) >> 32;
	return RRand;
}

INT_64 randomKey(int treeSize)
{
	return lineRand();
}

INT_64 randomOddKey(int treeSize)
{
	int k = lineRand() % (10000 * treeSize);
	k = k + !(k % 2);
	return k;
}

INT_64 randomEvenKey(int treeSize)
{
	int k = lineRand() % (10000 * treeSize);
	k = k + k % 2;
	return k;
}

template<class Key, class Data>
void testTree(Lab2::BST<Key, Data>& tree, Key* keys, Key (*getMissKey)(int), Key (*getSuccessKey)(int), double theoreticalComplexity)
{
	int size = tree.GetSize();
	cout << endl << "Размер дерева до теста: " << size << endl;

	int addReadedElements = 0;
	int removeReadedElements = 0;
	int searchReadedElements = 0;

	int probabilityOfMiss = 10;
	int operationsCount = size / 2;

	for (int i = 0; i < operationsCount; i++)
		if (i % probabilityOfMiss == 0) //miss
		{
			tree.Remove(getMissKey(size));
			removeReadedElements += tree.GetReadedElementsCount();

			tree.Add(keys[rand() % size], 1);
			addReadedElements += tree.GetReadedElementsCount();

			try {
				tree[getMissKey(size)];
			}
			catch (const char* ex) {}
			searchReadedElements += tree.GetReadedElementsCount();
		}
		else //success
		{
			int index = rand() % size;
			tree.Remove(keys[index]);
			removeReadedElements += tree.GetReadedElementsCount();

			Key key = getSuccessKey(size);
			tree.Add(key, 1);
			addReadedElements += tree.GetReadedElementsCount();

			keys[index] = key;
			try {
				tree[keys[rand() % size]];
			}
			catch (const char* ex) {}
			searchReadedElements += tree.GetReadedElementsCount();
		}

	cout << "Размер дерева после теста:" << tree.GetSize() << endl;

	cout << "Тёоретическая трудоёмкость:" << theoreticalComplexity << endl;

	cout << "Трудоёмкость вставки: " << addReadedElements * 1.0 / operationsCount << endl;
	cout << "Трудоёмкость удаления: " << removeReadedElements * 1.0 / operationsCount << endl;
	cout << "Трудоёмкость поиска: " << searchReadedElements * 1.0 / operationsCount << endl;
}

void testRandomTree(int size)
{
	BST< INT_64, int > tree;
	INT_64* keys = new INT_64[size];

	setFirstRandomDigit();

	for (int i = 0; i < size; i++)
	{
		keys[i] = lineRand();
		tree.Add(keys[i], 1);
	}

	double theoreticalComplexity = 1.39 * (log((double)size) / log(2.0));
	testTree(tree, keys, randomKey, randomKey, theoreticalComplexity);

	delete[] keys;
}

void testOrdinaryTree(int size)
{
	BST< INT_64, int > tree;
	INT_64* keys = new INT_64[size];

	for (int i = 0; i < size; i++) {
		keys[i] = i * 10000;
		tree.Add(keys[i], 1);
	}
	
	double theoreticalComplexity = tree.GetSize() * 1.0 / 2;
	testTree(tree, keys, randomOddKey, randomEvenKey, theoreticalComplexity);

	delete[] keys;
} 

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
	case 9:
		testRandomTree(inputValue("Размер тестируемого дерева"));
		break;
	case 10:
		testOrdinaryTree(inputValue("Размер тестируемого дерева"));
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
		"Вывести дерево", //0
		"Очистить дерево", //1
		"Добавить элемент", //2
		"Получить элемент по ключу", //3
		"Изменить элемент по ключу", //4
		"Удалить элемент по ключу", //5
		"Получить размер дерева", //6
		"Количество просмотренных элементов", //7
		"Вывести список ключей (L -> R -> t)", //8
		"Тест трудоёмкости случайного дерева", //9
		"Тест трудоёмкости вырожденного дерева" //10
	};

	Lab2::BST<int, int> bst;
	Lab2::BST<int, int>::Iterator iter;

	printCommands(commands);
	
	while (true)
	{
		handleInput(inputValue("Номер команды"), bst);
	}

}