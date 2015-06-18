#define _CRT_SECURE_NO_WARNINGS
#include "Runs.h"
#include <iostream>
#include <cstdio>

using namespace std;

vector<int> generateRandomString(int size, int sygma)
{
	vector<int> result(size + 1);
	for (int i = 0; i < size; i++)
	{
		result[i] = rand() % (sygma - 1) + 1;
	}
	return result;
}

vector<int> array;
long long runsCount = 0, periodsSum = 0, lengthSum = 0, sumPrecalc = 0, sumRunsTime = 0;

vector<Run> runs;

void addStats()
{
	sort(runs.begin(), runs.end());
	auto it = unique(runs.begin(), runs.end());
	runs.resize(it - runs.begin());
	runsCount += runs.size();
	for (int i = 0; i < runs.size(); i++)
	{
		periodsSum += runs[i].p;
		lengthSum += runs[i].j - runs[i].i + 1;
	}
	sumPrecalc += precalcEnd - precalcBegin;
	sumRunsTime += calcEnd - precalcEnd;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, sygma, k;
	scanf("%d%d%d", &n, &sygma, &k);
	srand(time(NULL));
	sygma++;
	for (int i = 0; i < k; i++)
	{
		array.clear();
		array = generateRandomString(n, sygma);
		runs.clear();
		runs = calculateRuns(array, sygma);
		addStats();
	}
	printf("Runs count   | Period   | Length  | Precalc time (ms) | Runs calc time\n%-15.6lf%-11.6lf%-13.6lf%-17.3lf%.3lf",
		runsCount * 1.0 / k, periodsSum * 1.0 / runsCount, lengthSum * 1.0 / runsCount, sumPrecalc * 1.0 / k, sumRunsTime * 1.0 / k);
	return 0;
}