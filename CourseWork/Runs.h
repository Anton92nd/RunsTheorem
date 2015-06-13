#include "SuffixArray.h"
#include "rmq.h"

using namespace std;

struct Run{
	int i, j, p;
	Run() : i(0), j(0), p(0){}
	Run(int _i, int _j, int _p) : i(_i), j(_j), p(_p){}

	bool operator<(const Run & other)const
	{
		if (i != other.i)
			return i < other.i;
		if (j != other.j)
			return j < other.j;
		return p < other.p;
	}

	bool operator==(const Run & other)const
	{
		return i == other.i && j == other.j && p == other.p;
	}
};

vector<int> str, revStr, SA, revSA, ISA, revISA, LCP, revLCP;
RMQ rmq, revRmq;
int sygma, n;
vector<pii> stack;

int getLCS(int l, int r)
{
	if (l < 0)
		return 0;
	l = revISA[n - 1 - l];
	r = revISA[n - 1 - r];
	if (l > r)
		swap(l, r);
	return revRmq.getRMQ(l, r - 1);
}

int getLCP(int l, int r)
{
	l = ISA[l];
	r = ISA[r];
	if (l > r)
		swap(l, r);
	return rmq.getRMQ(l, r - 1);
}

vector<Run> calculateRuns(const vector<int> & s, int syg)
{
	n = s.size();
	str = s;
	sygma = syg + 1;
	revStr.resize(str.size());
	reverse_copy(str.begin(), str.end(), revStr.begin());
	SA = calculateSuffixArray(str, sygma);
	ISA = inverse(SA, str.size());
	revSA = calculateSuffixArray(revStr, sygma);
	revISA = inverse(revSA, revStr.size());
	LCP = calculateLCP(str, SA);
	revLCP = calculateLCP(revStr, revSA);
	rmq = RMQ(LCP);
	revRmq = RMQ(revLCP);
	vector<Run> runs;
	stack.push_back(pii(n - 1, n - 1));
	for (int i = n - 2; i >= 0; i--)
	{
		int j = i;
		while (stack.size() > 1)
		{
			pii top = stack[stack.size() - 1];
			if (!(ISA[i] < ISA[top.first]))
				break;
			j = top.second;
			stack.pop_back();
		}
		stack.push_back(pii(i, j));
		int lcs = getLCS(i - 1, j);
		int lcp = getLCP(i, j + 1);
		int i1 = i - lcs;
		int j1 = j + lcp;
		int p = j - i + 1;
		if (j1 - i1 + 1 >= 2 * p && i1 < i && i <= i1 + p)
		{
			runs.push_back(Run(i1, j1, p));
		}
	}
	stack.clear();
	stack.push_back(pii(n - 1, n - 1));
	for (int i = n - 2; i >= 0; i--)
	{
		int j = i;
		while (stack.size() > 1)
		{
			pii top = stack[stack.size() - 1];
			if (ISA[i] < ISA[top.first])
				break;
			j = top.second;
			stack.pop_back();
		}
		stack.push_back(pii(i, j));
		int lcs = getLCS(i - 1, j);
		int lcp = getLCP(i, j + 1);
		int i1 = i - lcs;
		int j1 = j + lcp;
		int p = j - i + 1;
		if (j1 - i1 + 1 >= 2 * p && i1 < i && i <= i1 + p)
		{
			runs.push_back(Run(i1, j1, p));
		}
	}
	sort(runs.begin(), runs.end());
	auto it = unique(runs.begin(), runs.end());
	runs.resize(it - runs.begin());
	return runs;
}