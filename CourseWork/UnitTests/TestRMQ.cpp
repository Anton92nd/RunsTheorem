#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\rmq.h"
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TestRMQ)
	{
	private:
		void verifyTreeEquality(Pnode expected, Pnode tree)
		{
			Assert::IsFalse((expected == NULL) ^ (tree == NULL));
			if (expected == NULL)
				return;
			Assert::AreEqual(expected->x, tree->x);
			Assert::AreEqual(expected->y, tree->y);
			Assert::IsFalse((expected->l == NULL) ^ (tree->l == NULL));
			verifyTreeEquality(expected->l, tree->l);
			Assert::IsFalse((expected->r == NULL) ^ (tree->r == NULL));
			verifyTreeEquality(expected->r, tree->r);
		}
	public:

		TEST_METHOD(TestTree)
		{
			vector<int> numbers = {2, 3, 0, 3, 4, 1};
			RMQ rmq(numbers);
			Pnode tree = rmq.getTree();
			Pnode expected = new Node(2, 0, new Node(0, 2, NULL, new Node(1, 3)), 
				new Node(5, 1, new Node(3, 3, NULL, new Node(4, 4)), NULL));
			verifyTreeEquality(expected, tree);
		}

		TEST_METHOD(TestPairs)
		{
			vector<int> numbers = { 2, 3, 0, 3, 4, 1 };
			RMQ rmq(numbers);
			auto result = rmq.getPairs();
			vector<pii> expected = 
			{
				pii(2, 0), pii(0, 1), pii(1, 2), pii(0, 1), pii(2, 0),
				pii(5, 1), pii(3, 2), pii(4, 3), pii(3, 2), pii(5, 1), pii(2, 0)
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