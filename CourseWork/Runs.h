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

vector<Run> merge(const vector<Run> & a, const vector<Run> & b)
{
	vector<Run> result;
	result.reserve(a.size() + b.size());
	int i, j;
	for (i = 0, j = 0; i < a.size() && j < b.size();)
	{
		if (a[i] == b[j])
		{
			j++;
			continue;
		}
		if (a[i] < b[j])
		{
			result.push_back(a[i++]);
		}
		else
		{
			result.push_back(b[j++]);
		}
	}
	for (; i < a.size(); i++)
	{
		result.push_back(a[i]);
	}
	for (; j < b.size(); j++)
	{
		result.push_back(b[j]);
	}
	return result;
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
	vector<Run> runs[2];
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
			runs[0].push_back(Run(i1, j1, p));
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
			runs[1].push_back(Run(i1, j1, p));
		}
	}
	reverse(runs[0].begin(), runs[0].end());
	reverse(runs[1].begin(), runs[1].end());
	return merge(runs[0], runs[1]);
}