#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab1/List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestAddAndBrackets1)
		{
			Lab1::List<int> list(20);
			list.Add(2);
			list.Add(3);
			Assert::IsTrue(2 == list[0]);
			Assert::IsTrue(3 == list[1]);
		}

		TEST_METHOD(TestBrackets2)
		{
			Lab1::List<int> list(20);
			list.Add(2);
			list.Add(3);

			list[0] = 5;

			Assert::IsTrue(5 == list[0]);
			Assert::IsTrue(3 == list[1]);
		}

		TEST_METHOD(TestContains1)
		{
			Lab1::List<int> list(20);
			list.Add(2);
			list.Add(3);
			Assert::IsTrue(list.Contains(2));
			Assert::IsTrue(list.Contains(3));
			Assert::IsFalse(list.Contains(0));
		}

		TEST_METHOD(TestGetPos1)
		{
			Lab1::List<int> list(20);
			list.Add(2);
			list.Add(3);
			Assert::IsTrue(0 == list.GetPos(2));
			Assert::IsTrue(1 == list.GetPos(3));
		}

		TEST_METHOD(TestAdd2)
		{
			Lab1::List<int> list(20);
			list.Add(2, 0);
			Assert::IsTrue(2 == list[0]);

			list.Add(5, 0);

			Assert::IsTrue(5 == list[0]);
			Assert::IsTrue(2 == list[1]);

			list.Add(6, 1);

			Assert::IsTrue(5 == list[0]);
			Assert::IsTrue(6 == list[1]);
			Assert::IsTrue(2 == list[2]);
		}

		TEST_METHOD(TestRemoveByValue1)
		{
			Lab1::List<int> list(20);
			list.Add(2);
			list.Add(3);
			list.RemoveByValue(2);

			Assert::IsTrue(3 == list[0]);		
		}

		TEST_METHOD(TestRemoveByValue2)
		{
			Lab1::List<int> list(20);
			list.Add(2);
			list.Add(3);
			list.RemoveByValue(3);

			Assert::IsTrue(2 == list[0]);
		}

		TEST_METHOD(TestRemoveByPos1)
		{
			Lab1::List<int> list(20);
			list.Add(2);
			list.Add(3);
			list.RemoveByPos(0);

			Assert::IsTrue(3 == list[0]);

			list.Add(2);

			list.RemoveByPos(1);
			list.Add(4);

			Assert::IsTrue(4 == list[1]);
		}

		TEST_METHOD(TestChangeCapacity1)
		{
			Lab1::List<int> list(20);
			list.Add(1);
			list.Add(2);
			list.Add(3);
			list.Add(4);

			list.ChangeCapacity(3);
			Assert::IsTrue(1 == list[0]);
			Assert::IsTrue(2 == list[1]);
			Assert::IsTrue(3 == list[2]);
			Assert::IsTrue(4 == list[3]);
		}


	};
}
