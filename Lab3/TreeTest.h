#include <iostream>
#include "Tree23.h"

using namespace Lab3;
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
	INT_64 k = lineRand() % (10000 * treeSize);
	k = k + !(k % 2);
	return k;
}

INT_64 randomEvenKey(int treeSize)
{
	INT_64 k = lineRand() % (10000 * treeSize);
	k = k + k % 2;
	return k;
}

template<class K, class V>
void testTree(Tree23<K, V>& tree, K* keys, K(*getMissKey)(int), K(*getSuccessKey)(int), double theoreticalComplexity)
{
	const int size = tree.GetSize();
	cout << "Размер дерева до теста: " << size << endl;

	int addReadElements = 0;
	int removeReadElements = 0;
	int searchReadElements = 0;

	const int probabilityOfMiss = 10;
	const int operationsCount = size / 2;

	for (int i = 0; i < operationsCount; i++)
	{
		if (i % probabilityOfMiss == 0) //miss
		{
			tree.Remove(getMissKey(size));
			removeReadElements += tree.GetReadElementsCount();

			tree.Add(keys[lineRand() % size], 1);
			addReadElements += tree.GetReadElementsCount();

			try
			{
				tree.Get(getMissKey(size));
			}
			catch (const char* ex) {}
			searchReadElements += tree.GetReadElementsCount();
		}
		else //success
		{
			int index = lineRand() % size;
			tree.Remove(keys[index]);
			removeReadElements += tree.GetReadElementsCount();

			K key = getSuccessKey(size);
			tree.Add(key, 1);
			addReadElements += tree.GetReadElementsCount();
			keys[index] = key;

			try
			{
				tree.Get(keys[lineRand() % size]);
			}
			catch (const char* ex) {}
			searchReadElements += tree.GetReadElementsCount();
		}
	}

	cout << "Размер дерева после теста:" << tree.GetSize() << endl;

	cout << "Теоретическая трудоёмкость:" << theoreticalComplexity << endl;

	cout << "Трудоёмкость вставки: " << addReadElements * 1.0 / operationsCount << endl;
	cout << "Трудоёмкость удаления: " << removeReadElements * 1.0 / operationsCount << endl;
	cout << "Трудоёмкость поиска: " << searchReadElements * 1.0 / operationsCount << endl;
}

void testRandomTree(int size)
{
	Tree23< INT_64, int > tree;
	INT_64* keys = new INT_64[size];

	setFirstRandomDigit();

	for (int i = 0; i < size; i++)
	{
		keys[i] = lineRand();
		tree.Add(keys[i], 1);
	}

	double theoreticalComplexity = log2((double)size);
	testTree(tree, keys, randomKey, randomKey, theoreticalComplexity);

	delete[] keys;
}

void testOrdinaryTree(int size)
{
	Tree23< INT_64, int > tree;
	INT_64* keys = new INT_64[size];

	setFirstRandomDigit();

	for (int i = 0; i < size; i++) {
		keys[i] = i * 10000;
		tree.Add(keys[i], 1);
	}

	double theoreticalComplexity = log2((double)size);
	testTree(tree, keys, randomOddKey, randomEvenKey, theoreticalComplexity);

	delete[] keys;
}