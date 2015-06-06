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

	};
}