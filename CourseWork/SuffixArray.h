#include <algorithm>
#include <vector>
#include <cassert>
#define DEBUG 1

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> trii;

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

vector<pii> stableSortPairsByFirst(const vector<pii> & pairs, int sygma)
{
	vector<int> baskets, pointers;
	baskets.resize(sygma);
	pointers.resize(sygma);
	for (int i = 0; i < pairs.size(); i++)
	{
		baskets[pairs[i].first]++;
	}
	for (int i = 1; i < sygma; i++)
	{
		pointers[i] = pointers[i - 1] + baskets[i - 1];
	}
	vector<pii> result;
	result.resize(pairs.size());
	for (int i = 0; i < pairs.size(); i++)
	{
		result[pointers[pairs[i].first]] = pairs[i];
		pointers[pairs[i].first]++;
	}
	return result;
}

vector<int> getAs0(const vector<int> & s, const vector<int> & As12, int sygma)
{
	vector<pii> M;
	for (int i = 0; i < 2 * s.size() / 3; i++)
	{
		if (As12[i] % 3 == 1)
			M.push_back(pii(s[As12[i] - 1], As12[i]));
	}
	M = stableSortPairsByFirst(M, sygma);
	vector<int> result;
	result.resize(M.size());
	for (int i = 0; i < M.size(); i++)
	{
		result[i] = M[i].second - 1;
	}
	return result;
}

vector<int> inverse(const vector<int> & v, int sz)
{
	vector<int> result;
	result.resize(sz);
	for (int i = 0; i < v.size(); i++)
	{
		result[v[i]] = i;
	}
	return result;
}

vector<int> mergeParts(const vector<int> & s, const vector<int> & As0, const vector<int> & As12)
{
	vector<int> result;
	result.reserve(s.size());
	vector<int> rank = inverse(As12, s.size());
	int i, j;
	for (i = 0, j = 0; i < As12.size() && j < As0.size();)
	{
		int pos12 = As12[i];
		int pos0 = As0[j];
		if (pos12 % 3 == 1)
		{
			if (pii(s[pos12], pos12 + 1 < s.size() ? rank[pos12 + 1] : 0) 
				< pii(s[pos0], pos0 + 1 < s.size() ? rank[pos0 + 1] : 0))
			{
				result.push_back(pos12);
				i++;
			}
			else
			{
				result.push_back(pos0);
				j++;
			}
		}
		else
		{
			if (trii(s[pos12], pii(pos12 + 1 < s.size() ? s[pos12 + 1] : 0, pos12 + 2 < s.size() ? rank[pos12 + 2] : 0)) 
				< trii(s[pos0], pii(pos0 + 1 < s.size() ? s[pos0 + 1] : 0, pos0 + 2 < s.size() ? rank[pos0 + 2] : 0)))
			{
				result.push_back(pos12);
				i++;
			}
			else
			{
				result.push_back(pos0);
				j++;
			}
		}
	}
	for (; i < As12.size(); i++)
	{
		result.push_back(As12[i]);
	}
	for (; j < As0.size(); j++)
	{
		result.push_back(As0[j]);
	}
	return result;
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
	int n = s.size();
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
	for (int i = 0; i < As12.size(); i++)
	{
		As12[i] = (As12[i] < n / 3) ? 3 * As12[i] + 1 : 3 * (As12[i] - n / 3) + 2;
	}
	vector<int> As0 = getAs0(s, As12, sygma);
	return mergeParts(s, As0, As12);
}