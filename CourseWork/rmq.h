#include <algorithm>
#include <vector>
#define DEBUG 1

using namespace std;

struct Node{
	int x, y;
	Node *l, *r, *p;
	Node() : x(0), y(0), l(NULL), r(NULL), p(NULL){}
	Node(int _x, int _y) : x(_x), y(_y), l(NULL), r(NULL), p(NULL){}
	Node(int _x, int _y, Node *_l, Node *_r) : x(_x), y(_y), l(_l), r(_r){}
};

typedef Node* Pnode;
typedef pair<int, int> pii;

class RMQ
{
private:
	vector<int> array;
	vector<pii> pairs;
	vector<int> first;
	Pnode tree;

	void appendNode(Pnode & root, Pnode & last, Pnode v)
	{
		while (last != NULL && last->y > v->y)
		{
			last = last->p;
		}
		if (last == NULL)
		{
			v->l = root;
			root->p = v;
			root = v;
			last = root;
			return;
		}
		v->l = last->r;
		if (last->r != NULL)
		{
			last->r->p = v;
		}
		last->r = v;
		v->p = last;
		last = v;
	}

	Pnode buildCartesian()
	{
		Pnode root = new Node(0, array[0]);
		Pnode last = root;
		for (int i = 1; i < array.size(); i++)
		{
			appendNode(root, last, new Node(i, array[i]));
		}
		return root;
	}

	void printCartesian(Pnode T)
	{
		if (T == NULL)
			return;
		printCartesian(T->l);
		printf("%d %d\n", T->x, T->y);
		printCartesian(T->r);
	}

	void buildPairs(Pnode T, int depth)
	{
		first[T->x] = pairs.size();
		pairs.push_back(pii(T->x, depth));
		if (T->l != NULL)
		{
			buildPairs(T->l, depth + 1);
			pairs.push_back(pii(T->x, depth));
		}
		if (T->r != NULL)
		{
			buildPairs(T->r, depth + 1);
			pairs.push_back(pii(T->x, depth));
		}
	}

	void buildYourself()
	{
		tree = buildCartesian();
		if (DEBUG)
			printCartesian(tree);
		pairs.reserve(2 * array.size());
		first.resize(array.size());
		buildPairs(tree, 0);
		if (DEBUG)
		{
			printf("RMQ +/-1:\n");
			for (int i = 0; i < pairs.size(); i++)
			{
				printf("%d %d\n", pairs[i].first, pairs[i].second);
			}
		}
	}
public:
	RMQ(vector<int> array)
	{
		this->array = array;
		buildYourself();
	}

	vector<pii> getPairs()
	{
		return pairs;
	}

	Pnode getTree()
	{
		return tree;
	}
};