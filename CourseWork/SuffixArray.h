#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

vector<int> sortSimple(vector<int> s)
{
	return vector<int>();
}

bool compareTriples(int* a, int* b)
{
	return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}

vector<int*> sortTriples(vector<int*> triples, int sygma)
{
	vector<int> baskets, pointers;
	vector<int*> temp;
	temp.resize(triples.size());
	for (int j = 2; j >= 0; j--)
	{
		baskets.clear();
		baskets.resize(sygma, 0);
		pointers.clear();
		pointers.resize(sygma, 0);
		for (int i = 0; i < triples.size(); i++)
		{
			baskets[triples[i][j]]++;
		}
		for (int i = 1; i < sygma; i++)
		{
			pointers[i] = pointers[i - 1] + baskets[i - 1];
		}
		for (int i = 0; i < triples.size(); i++)
		{
			int pnt = triples[i][j];
			temp[pointers[pnt]++] = triples[i];
		}
		triples = temp;
		for (int i = 0; i < triples.size(); i++)
		{
			printf("%d %d %d\n", triples[i][0], triples[i][1], triples[i][2]);
		}
		printf("\n");
	}
	auto it = unique(triples.begin(), triples.end(), compareTriples);
	triples.resize(it - triples.begin());
	return triples;
}

vector<int> getS1S2(const vector<int> & s, int sygma)
{
	vector<int*> triples;
	triples.reserve(s.size());
	for (int i = 0; i < s.size(); i++)
	{
		if (i % 3 != 0)
		{
			triples.push_back(new int[3] {s[i], (i + 1 < s.size() ? s[i + 1] : 0), (i + 2 < s.size() ? s[i + 2] : 0)});
		}
	}
	triples = sortTriples(triples, sygma);
	for (int i = 0; i < triples.size(); i++)
	{
		printf("%d %d %d\n", triples[i][0], triples[i][1], triples[i][2]);
	}
	return vector<int>();
}

vector<int> calculateSuffixArray(vector<int> s, int sygma)
{
	if (s.size() <= 4)
	{
		return sortSimple(s);
	}
	while (s.size() % 3)
	{
		s.push_back(0);
	}
	vector<int> s1s2 = getS1S2(s, sygma);
	return vector<int>();
}