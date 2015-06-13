#define _CRT_SECURE_NO_WARNINGS
#include "Runs.h"
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
	vector<Run> runs = calculateRuns(array, sygma);
	printf("Runs:\n");
	for (int i = 0; i < runs.size(); i++)
	{
		printf("%d %d %d\n", runs[i].i + 1, runs[i].j + 1, runs[i].p);
	}
	return 0;
}