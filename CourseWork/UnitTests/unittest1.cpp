#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SuffixArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(TestSuffixArray)
	{
	public:
		
		TEST_METHOD(TestSmallArray)
		{
			vector<int> str = { 1, 2, 1, 0 };
			auto result = calculateSuffixArray(str, 3);
			Assert::AreEqual(4, (int) result.size());
			vector<int> expected = { 3, 2, 0, 1 };
			for (int i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(expected[i], result[i]);
			}
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

	};
}