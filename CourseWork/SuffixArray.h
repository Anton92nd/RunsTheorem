#include <algorithm>
#include <vector>
#include <cassert>
#define DEBUG 1

using namespace std;

typedef pair<int, int> pii;

bool isLess(const vector<int> & s, int a, int b)
{
	while (a < s.size() && b < s.size() && s[a] == s[b])
	{
		a++, b++;
	}
	if (a == s.size() || b == s.size())
	{
		return a == s.size();
	}
	return s[a] < s[b];
}

vector<int> sortSimple(vector<int> s)
{
	vector<int> result;
	result.resize(s.size());
	for (int i = 0; i < s.size(); i++)
	{
		result[i] = i;
	}
	for (int i = 0; i < s.size(); i++)
	{
		for (int j = s.size() - 1; j > i; j--)
		{
			if (isLess(s, result[j], result[j - 1]))
			{
				swap(result[j], result[j - 1]);
			}
		}
	}
	return result;
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
	}
	auto it = unique(triples.begin(), triples.end(), compareTriples);
	triples.resize(it - triples.begin());
	return triples;
}

int findTriple(const vector<int*> & triples, int a, int b, int c)
{
	for (int i = 0; i < triples.size(); i++)
	{
		if (a == triples[i][0] && b == triples[i][1] && c == triples[i][2])
			return i;
	}
	assert(true);
	return -1;
}

vector<int> encodedByTriples(const vector<int> & s, const vector<int*> &triples)
{
	vector<int> result;
	for (int i = 0; i < s.size(); i += 3)
	{
		result.push_back(findTriple(triples, s[i], s[i + 1], s[i + 2]));
	}
	return result;
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
	if (DEBUG)
	{
		printf("Triples sorted:\n");
		for (int i = 0; i < triples.size(); i++)
		{
			printf("%d %d %d\n", triples[i][0], triples[i][1], triples[i][2]);
		}
	}
	vector<int> s1s2;
	s1s2.reserve(2 * s.size());
	for (int i = 1; i < s.size(); i++)
	{
		s1s2.push_back(s[i]);
	}
	s1s2.push_back(0);
	for (int i = 2; i < s.size(); i++)
	{
		s1s2.push_back(s[i]);
	}
	s1s2.push_back(0);
	s1s2.push_back(0);
	return encodedByTriples(s1s2, triples);
}

vector<int> calculateSuffixArray(vector<int> & s, int sygma)
{
	if (DEBUG)
	{
		printf("Calculating array for: ");
		for (int i = 0; i < s.size(); i++)
		{
			printf("%d ", s[i]);
		}
		printf("\n");
	}
	if (s.size() <= 4)
	{
		return sortSimple(s);
	}
	while (s.size() % 3)
	{
		s.push_back(0);
	}
	vector<int> s1s2 = getS1S2(s, sygma);
	if (DEBUG)
	{
		printf("S12 encoded by triples:\n");
		for (int i = 0; i < s1s2.size(); i++)
		{
			printf("%d ", s1s2[i]);
		}
		printf("\n");
	}
	int newSygma = *max_element(s1s2.begin(), s1s2.end()) + 1;
	vector<int> As12 = calculateSuffixArray(s1s2, newSygma);
	return vector<int>();
}