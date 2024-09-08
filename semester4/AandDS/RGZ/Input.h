#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <queue>

using namespace std;

template <typename T>
class Input
{
public:
	static T Get(string hintForUser);
	static queue<T>& GetPredefinedValues(); //workarond for mocking input in tests. Every Get() method doesnt firstly access predefinedValues due to some tricky sharing problems :(
private:
	static inline queue<T> predefinedValues;
};

template <typename T>
queue<T>& Input<T>::GetPredefinedValues()
{
	return predefinedValues;
}

template<typename T>
inline T Input<T>::Get(string hintForUser)
{
	T value; cin >> value;
	return value;
}

template<>
inline int Input<int>::Get(string hintForUser)
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

template<>
inline bool Input<bool>::Get(string hintForUser)
{
	int input = Input<int>::Get(hintForUser + " (0/1) ");

	while (input > 1 || input < 0)
	{
		cout << "Only 0 or 1\n";
		cin >> input;
	}

	return (bool)input;
}

template<>
inline string Input<string>::Get(string hintForUser)
{
	cout << hintForUser << ":";
	string input;
	getline(cin, input);
	return input;
}