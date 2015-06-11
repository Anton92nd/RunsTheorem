#include <algorithm>
#include <vector>

using namespace std;

struct Node{
	int x, y;
	Node *l, *r, *p;
	Node() : x(0), y(0), l(NULL), r(NULL), p(NULL){}
	Node(int _x, int _y) : x(_x), y(_y), l(NULL), r(NULL), p(NULL){}
};

typedef Node* Pnode;
typedef pair<int, int> pii;

class RMQ
{
private:
	vector<int> array;
	vector<pii> pairs;

	void appendNode(Pnode & root, Pnode & last, Pnode v)
	{
		while (last != NULL && last->y > v->y)
		{
			last = last->p;
		}
		if (last == NULL)
		{
			v->l = root;
			root = v;
			last = root;
			return;
		}
		v->l = last->r;
		last->r = v;
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

	void buildYourself()
	{
		Pnode root = buildCartesian();
		printCartesian(root);
	}
public:
	RMQ(vector<int> array)
	{
		this->array = array;
		buildYourself();
	}
};