#define _CRT_SECURE_NO_WARNINGS
#include "SuffixArray.h"
#include <iostream>
#include <cstdio>

using namespace std;

vector<int> array, result;

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
	result = calculateSuffixArray(array, sygma + 1);
	for (int i = 0; i < result.size(); i++)
	{
		printf("%d ", result[i]);
	}
	return 0;
}