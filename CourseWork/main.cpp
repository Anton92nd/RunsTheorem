#define _CRT_SECURE_NO_WARNINGS
#include "SuffixArray.h"
#include "rmq.h"
#include <iostream>
#include <cstdio>

using namespace std;

vector<int> array, sa, lcp;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int length, sygma;
	scanf("%d%d\n", &length, &sygma);
	array.reserve(length);
	for (int i = 0; i < length; i++)
	{
		char c;
		scanf("%c", &c);
		array.push_back(c - 'a' + 1);
	}
	array.push_back(0);
	sa = calculateSuffixArray(array, sygma + 1);
	if (DEBUG)
	{
		printf("Result:\n");
	}
	for (int i = 0; i < sa.size(); i++)
	{
		printf("%d ", sa[i]);
	}
	printf("\n");
	lcp = calculateLCP(array, sa);
	if (DEBUG)
	{
		printf("LCP:\n");
		for (int i = 0; i < lcp.size(); i++)
		{
			printf("%d ", lcp[i]);
		}
		printf("\n");
	}
	RMQ rmq(lcp);
	return 0;
}