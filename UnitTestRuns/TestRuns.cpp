#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\CourseWork\Runs.h"
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestRuns
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		void verifyEquality(const vector<Run> & expected, const vector<Run> & actual)
		{
			Assert::AreEqual(expected.size(), actual.size());
			for (int i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(expected[i].i, actual[i].i);
				Assert::AreEqual(expected[i].j, actual[i].j);
				Assert::AreEqual(expected[i].p, actual[i].p);
			}
		}

		vector<int> generateRandomString(int size, int sygma)
		{
			vector<int> result(size + 1);
			for (int i = 0; i < size; i++)
			{
				result[i] = rand() % (sygma - 1) + 1;
			}
			return result;
		}

	public:
		
		TEST_METHOD_INITIALIZE(SetUp)
		{
			srand(time(NULL));
		}

		TEST_METHOD(TestSimpleString)
		{
			vector<int> str = { 1, 2, 1, 2, 1, 3, 1, 1, 0 };
			auto result = calculateRuns(str, 4);
			vector<Run> expected = {
				Run(0, 4, 2), Run(6, 7, 1)
			};
			verifyEquality(expected, result);
		}

		TEST_METHOD(TestLongerString)
		{
			vector<int> str = {
				3, 1, 2, 1, 2, 1, 3, 1, 2, 1, 2, 1, 3,
				1, 2, 3, 1, 2, 3, 2, 2, 0 };
			auto result = calculateRuns(str, 4);
			vector<Run> expected = {
				Run(0, 14, 6), Run(1, 5, 2), Run(7, 11, 2),
				Run(12, 18, 3), Run(19, 20, 1)
			};
			verifyEquality(expected, result);
		}

		TEST_METHOD(TestRuns1000_2)
		{
			auto str = generateRandomString(1000, 3);
			auto result = calculateRuns(str, 3);
		}

		TEST_METHOD(TestRuns1000_3)
		{
			auto str = generateRandomString(1000, 4);
			auto result = calculateRuns(str, 4);
		}

		TEST_METHOD(TestRuns10000_2)
		{
			auto str = generateRandomString(10000, 3);
			auto result = calculateRuns(str, 3);
		}

		TEST_METHOD(TestRuns10000_3)
		{
			auto str = generateRandomString(10000, 4);
			auto result = calculateRuns(str, 4);
		}

		TEST_METHOD(TestRuns100000_2)
		{
			auto str = generateRandomString(100000, 3);
			auto result = calculateRuns(str, 3);
		}

		TEST_METHOD(TestRuns100000_3)
		{
			auto str = generateRandomString(100000, 4);
			auto result = calculateRuns(str, 4);
		}

		TEST_METHOD(TestRuns100000_26)
		{
			auto str = generateRandomString(100000, 27);
			auto result = calculateRuns(str, 27);
		}

		TEST_METHOD(TestRuns1000000_2)
		{
			auto str = generateRandomString(1000000, 3);
			auto result = calculateRuns(str, 3);
		}

		TEST_METHOD(TestRuns1000000_3)
		{
			auto str = generateRandomString(1000000, 4);
			auto result = calculateRuns(str, 4);
		}
	};
}