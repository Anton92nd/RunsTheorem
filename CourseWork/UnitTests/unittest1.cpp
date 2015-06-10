#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SuffixArray.h"
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(TestSuffixArray)
	{
	private:
		vector<int> generateRandomString(int size, int sygma)
		{
			vector<int> result(size + 1);
			for (int i = 0; i < size; i++)
			{
				result[i] = rand() % (sygma - 1) + 1;
			}
			return result;
		}

		void verifySA(const vector<int> & array, const vector<int> & str)
		{
			Assert::AreEqual(array.size(), str.size());
			for (int i = 0; i < array.size() - 1; i++)
			{
				int pos1 = array[i], pos2 = array[i + 1];
				for (; pos1 < str.size() && pos2 < str.size() && str[pos1] == str[pos2]; pos1++, pos2++);
				Assert::IsFalse(pos2 == str.size());
				if (pos1 < str.size())
					Assert::IsTrue(str[pos1] < str[pos2]);
			}
		}
	public:
		
		TEST_METHOD_INITIALIZE(SetUp)
		{
			srand(time(NULL));
		}

		TEST_METHOD(TestSmallArray)
		{
			vector<int> str = { 1, 2, 1, 0 };
			auto result = calculateSuffixArray(str, 3);
			vector<int> expected = { 3, 2, 0, 1 };
			Assert::AreEqual(str.size(), result.size());
			for (int i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(expected[i], result[i]);
			}
		}

		TEST_METHOD(TestNotSmallArray)
		{
			vector<int> str = { 1, 2, 1, 2, 2, 2, 1, 1, 0 };
			auto result = calculateSuffixArray(str, 3);
			vector<int> expected = {8, 7, 6, 0, 2, 5, 1, 4, 3};
			Assert::AreEqual(str.size(), result.size());
			for (int i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(expected[i], result[i]);
			}
		}

		TEST_METHOD(TestSmallRandomString)
		{
			vector<int> str = generateRandomString(8, 3);
			auto result = calculateSuffixArray(str, 3);
			verifySA(result, str);
		}

		TEST_METHOD(TestMediumRandomString)
		{
			vector<int> str = generateRandomString(100, 15);
			auto result = calculateSuffixArray(str, 15);
			verifySA(result, str);
		}

		TEST_METHOD(TestSortedAndUniqueTriples)
		{
			vector<int*> triples;
			triples.push_back(new int[3] {2, 2, 1});
			triples.push_back(new int[3] {2, 1, 3});
			triples.push_back(new int[3] {3, 1, 2});
			triples.push_back(new int[3] {1, 2, 0});
			triples.push_back(new int[3] {0, 0, 0});
			triples.push_back(new int[3] {3, 1, 2});
			triples.push_back(new int[3] {3, 1, 3});
			auto result = sortTriples(triples, 4);
			vector<int*> expected;
			expected.push_back(new int[3] {0, 0, 0});
			expected.push_back(new int[3] {1, 2, 0});
			expected.push_back(new int[3] {2, 1, 3});
			expected.push_back(new int[3] {2, 2, 1});
			expected.push_back(new int[3] {3, 1, 2});
			expected.push_back(new int[3] {3, 1, 3});
			Assert::AreEqual(expected.size(), result.size());
			for (int i = 0; i < expected.size(); i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expected[i][j], result[i][j]);
				}
			}
		}


		TEST_METHOD(TestStableSortPairsByFirst)
		{
			vector<pii> toSort = 
			{
				pii(2, 1),
				pii(3, 2),
				pii(3, 3),
				pii(4, 4),
				pii(4, 5),
				pii(1, 6),
				pii(2, 7)
			};
			auto result = stableSortPairsByFirst(toSort, 10);
			vector<pii> expected = 
			{
				pii(1, 6),
				pii(2, 1),
				pii(2, 7),
				pii(3, 2),
				pii(3, 3),
				pii(4, 4),
				pii(4, 5)
			};
			Assert::AreEqual(expected.size(), result.size());
			for (int i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(expected[i].first, result[i].first);
				Assert::AreEqual(expected[i].second, result[i].second);
			}
		}
	};
}