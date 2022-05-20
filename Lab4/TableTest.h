#include <iostream>
#include <cctype>
#include "HashTable.h"

using namespace Lab4;
using namespace std;

using INT_64 = unsigned long long;

static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

const int STRING_SIZE = 15;

#define LINEAR_SUCCESS (0.5 * (1 + 1 / (1 - alpha)))
#define LINEAR_FAIL (0.5 * (1 + pow(1 / (1 - alpha), 2) ))
#define QUADRATIC_SUCCESS (-log(1-alpha) / alpha) 
#define QUADRATIC_FAIL (1.0 / (1 - alpha)) 
#define DOUBLE_HASH_SUCCESS (1.0 / alpha * log(1 / (1 - alpha)))
#define DOUBLE_HASH__FAIL (1.0 / (1 - alpha))

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

int randomInRange(int inclusiveMin, int inclusiveMax)
{
	return lineRand() % (inclusiveMax - inclusiveMin + 1) + inclusiveMin;
}

string randomUpperCaseString()
{
	string s;

	for (int i = 0; i < STRING_SIZE; i++)
	{
		s.insert(i, 1, (char)randomInRange(65,90));
	}

	return s;
}

string randomLowerCaseString()
{
	string s;

	for (int i = 0; i < STRING_SIZE; i++)
	{
		s.insert(i, 1, (char)randomInRange(97, 122));
	}

	return s;
}

template<class K, class V>
void testTable(HashTable<K, V>& table, K* keys, K(*getMissKey)(), K(*getSuccessKey)())
{
	const int size = table.GetSize();
	cout << "Коэффициент заполнения до теста:" << size * 1.0 / table.GetCapacity() << endl << endl;

	int addTrials = 0;
	int removeTrials = 0;
	int searchTrials = 0;

	const int probabilityOfMiss = 10;
	const int operationsCount = table.GetSize() / 2;

	for (int i = 0; i < operationsCount; i++)
	{
		if (i % probabilityOfMiss == 0) //miss
		{
			table.Remove(getMissKey());
			removeTrials += table.GetTrialsCount();

			table.Add(keys[lineRand() % size], 1);
			addTrials += table.GetTrialsCount();

			try
			{
				table[getMissKey()];
			}
			catch (const char* ex) {}
			searchTrials += table.GetTrialsCount();
		}
		else //success
		{
			int index = lineRand() % size;
			table.Remove(keys[index]);
			removeTrials += table.GetTrialsCount();

			K key = getSuccessKey();
			table.Add(key, 1);
			addTrials += table.GetTrialsCount();
			keys[index] = key;

			try
			{
				table[keys[lineRand() % size]];
			}
			catch (const char* ex) {}
			searchTrials += table.GetTrialsCount();
		}
	}

	printf("Статистический критерий распределения: %.1f (длина массива: %d)\n", table.GetHashQuality(), table.GetCapacity());
	cout << "Трудоёмкость вставки:" << addTrials * 1.0 / operationsCount << endl;
	cout << "Трудоёмкость удаления:" << removeTrials * 1.0 / operationsCount << endl;
	cout << "Трудоёмкость поиска:" << searchTrials * 1.0 / operationsCount << endl;
}

void testOpenAddr(int keysCount)
{
	HashTable< string, int > table(keysCount);

	float fullCoef;
	cout << "Коэффициент заполнения:";
	cin >> fullCoef;

	keysCount = table.GetCapacity() * fullCoef;

	string* keys = new string[keysCount];

	setFirstRandomDigit();

	for (int i = 0; i < keysCount; i++)
	{
		keys[i] = randomLowerCaseString();
		table.Add(keys[i], 1);
	}

	testTable(table, keys, randomUpperCaseString, randomLowerCaseString);

	float alpha = table.GetSize() * 1.0 / table.GetCapacity();
	cout << "Коэффициент заполнения после теста:" << alpha << endl;
	cout << "Теоретическая трудоёмкость удаления/поиска:" << 0.9 * DOUBLE_HASH_SUCCESS + 0.1 * DOUBLE_HASH__FAIL << endl;
	cout << "Теоретическая трудоёмкость вставки:" << 0.9 * DOUBLE_HASH__FAIL + 0.1 * DOUBLE_HASH_SUCCESS << endl << endl;

	delete[] keys;
}

void testChainsColl(int keysCount)
{
	HashTable< string, int > table(keysCount);
	table.SetForm(FormName::ChainsOfCollisions);

	float fullCoef;
	cout << "Коэффициент заполнения:";
	cin >> fullCoef;

	keysCount = table.GetCapacity() * fullCoef;

	string* keys = new string[keysCount];

	setFirstRandomDigit();

	for (int i = 0; i < keysCount; i++) {
		keys[i] = randomLowerCaseString();
		table.Add(keys[i], 1);
	}

	testTable(table, keys, randomUpperCaseString, randomLowerCaseString);

	float alpha = table.GetSize() * 1.0 / table.GetCapacity();
	cout << "Коэффициент заполнения после теста:" << alpha << endl;
	cout << "Теоретическая трудоёмкость удаления/поиска:" << 0.9 * (1 + alpha / 2) + 0.1*(1 + alpha) << endl;
	cout << "Теоретическая трудоёмкость вставки:" << 1 + alpha << endl << endl;

	delete[] keys;
}
