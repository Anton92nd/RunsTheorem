#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> trii;

struct Triple{
	int num;
	int ar[3];

	Triple()
	{
		num = 0;
		ar[0] = ar[1] = ar[2] = 0;
	}

	Triple(int _num, int _a, int _b, int _c)
	{
		num = _num;
		ar[0] = _a;
		ar[1] = _b;
		ar[2] = _c;
	}

	bool operator!=(const Triple & other)const
	{
		return ar[0] != other.ar[0] || ar[1] != other.ar[1] || ar[2] != other.ar[2];
	}
};

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

void sortTriples(vector<Triple> & triples, int sygma)
{
	vector<int> baskets, pointers;
	vector<Triple> temp;
	temp.resize(triples.size());
	for (int j = 2; j >= 0; j--)
	{
		baskets.clear();
		baskets.resize(sygma, 0);
		pointers.clear();
		pointers.resize(sygma, 0);
		for (int i = 0; i < triples.size(); i++)
		{
			baskets[triples[i].ar[j]]++;
		}
		for (int i = 1; i < sygma; i++)
		{
			pointers[i] = pointers[i - 1] + baskets[i - 1];
		}
		for (int i = 0; i < triples.size(); i++)
		{
			int pnt = triples[i].ar[j];
			temp[pointers[pnt]++] = triples[i];
		}
		triples = temp;
	}
}

vector<int> getS1S2(const vector<int> & s, int sygma)
{
	vector<Triple> triples;
	int n = s.size();
	for (int i = 1, j = 0; i < n; i += 3, j++)
	{
		triples.push_back(Triple(j, s[i], i + 1 < n ? s[i + 1] : 0, i + 2 < n ? s[i + 2] : 0));
	}
	for (int i = 2, j = n / 3; i < n; i += 3, j++)
	{
		triples.push_back(Triple(j, s[i], i + 1 < n ? s[i + 1] : 0, i + 2 < n ? s[i + 2] : 0));
	}
	sortTriples(triples, sygma);
	vector<int> result;
	result.resize(2 * n / 3);
	int num = 0;
	result[triples[0].num] = 0;
	for (int i = 1; i < triples.size(); i++)
	{
		num += (triples[i] != triples[i - 1]);
		result[triples[i].num] = num;
	}
	return result;
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
	int newSygma = *max_element(s1s2.begin(), s1s2.end()) + 1;
	vector<int> ss = calculateSuffixArray(s1s2, newSygma);
	vector<int> As12;
	As12.reserve(2 * n / 3);
	for (int i = 0; i < ss.size(); i++)
	{
		int newPos = (ss[i] < n / 3) ? 3 * ss[i] + 1 : 3 * (ss[i] - n / 3) + 2;
		if (newPos < s.size())
			As12.push_back(newPos);
	}
	vector<int> As0 = getAs0(s, As12, sygma);
	vector<int> result = mergeParts(s, As0, As12);
	while (result.size() > s.size())
		result.pop_back();
	return result;
}

vector<int> calculateLCP(const vector<int> & s, const vector<int> sa)
{
	int n = s.size();
	vector<int> isa = inverse(sa, n);
	vector<int> lcp(n);
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (k > 0) k--;
		if (isa[i] == n - 1)
		{
			lcp[n - 1] = -1;
			k = 0;
		}
		else
		{
			int j = sa[isa[i] + 1];
			while (max(i + k, j + k) < n && s[i + k] == s[j + k])
				k++;
			lcp[isa[i]] = k;
		}
	}
	return lcp;
}