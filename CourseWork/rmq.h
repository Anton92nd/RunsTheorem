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
	vector<int> depths, vertices;
	vector<int> first;
	vector<vector<vector<int>>> table;
	vector<int> blockTypes;
	vector<vector<int>> sparse;

	int blockSize;
	Pnode tree;

	void calculateBlockTypes()
	{
		vector<int> block;
		block.resize(blockSize);
		table.resize(1 << (blockSize - 1));
		for (int mask = 0; mask < (1 << (blockSize - 1)); mask++)
		{
			table[mask].resize(blockSize);
			block[0] = 0;
			for (int i = 0; i < blockSize - 1; i++)
			{
				block[i + 1] = block[i] + ((mask & (1 << i)) ? 1 : -1);
			}
			for (int i = 0; i < blockSize; i++)
			{
				table[mask][i].resize(blockSize + 1);
				int pos = i;
				for (int j = i + 1; j <= blockSize; j++)
				{
					table[mask][i][j] = pos;
					if (j < blockSize && block[j] < block[pos])
						pos = j;
				}
			}
		}
	}

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

	void buildPairs(Pnode T, int depth)
	{
		first[T->x] = vertices.size();
		depths.push_back(depth);
		vertices.push_back(T->x);
		if (T->l != NULL)
		{
			buildPairs(T->l, depth + 1);
			depths.push_back(depth);
			vertices.push_back(T->x);
		}
		if (T->r != NULL)
		{
			buildPairs(T->r, depth + 1);
			depths.push_back(depth);
			vertices.push_back(T->x);
		}
	}

	int getBlockType(int pos)
	{
		int mask = 0;
		for (int i = 0; i < blockSize - 1; i++)
		{
			if (depths[pos + i + 1] > depths[pos + i])
			{
				mask |= 1 << i;
			}
		}
		return mask;
	}

	void buildSparse()
	{
		blockSize = 0;
		while ((1 << blockSize) <= depths.size())
			blockSize++;
		blockSize = max(1, (blockSize - 1) / 2);
		calculateBlockTypes();
		while (depths.size() % blockSize)
		{
			depths.push_back(depths[depths.size() - 1] + 1);
			vertices.push_back(-1);
		}
		sparse.resize(depths.size() / blockSize);
		blockTypes.resize(sparse.size());
		int log = 0;
		while ((1 << log) <= sparse.size())
			log++;
		for (int i = 0; i < depths.size(); i += blockSize)
		{
			blockTypes[i / blockSize] = getBlockType(i);
			int pos = i + table[blockTypes[i / blockSize]][0][blockSize];
			sparse[i / blockSize].resize(log);
			sparse[i / blockSize][0] = pos;
		}
		for (int k = 0; k < log - 1; k++)
		{
			for (int i = 0; i + (1 << (k + 1)) <= sparse.size(); i++)
			{
				int x = sparse[i][k], y = sparse[i + (1 << k)][k];
				sparse[i][k + 1] = depths[x] <= depths[y]
					? sparse[i][k]
					: sparse[i + (1 << k)][k];
			}
		}
	}

	void buildYourself()
	{
		tree = buildCartesian();
		depths.reserve(2 * array.size());
		vertices.reserve(2 * array.size());
		first.resize(array.size());
		buildPairs(tree, 0);
		buildSparse();
	}

	int getInner(int l, int r)
	{
		int k = 0;
		while ((1 << k) <= (r - l)) k++;
		k--;
		int x = sparse[l][k], y = sparse[r - (1 << k)][k];
		return depths[x] <= depths[y] ? x : y;
	}

	int rmq(int l, int r)
	{
		int lblock = l / blockSize;
		int rblock = r / blockSize;
		if (lblock == rblock)
		{
			l %= blockSize;
			r %= blockSize;
			return array[
				vertices[
					lblock * blockSize + table[blockTypes[lblock]][l][r + 1]
				]
			];
		}
		int inner = lblock + 1 == rblock ? 2 * 1e9 : array[
			vertices[getInner(lblock + 1, rblock)]
		];
		int left = array[
			vertices[
				lblock * blockSize + table[blockTypes[lblock]][l % blockSize][blockSize]
			]
		];
		int right = array[
			vertices[
				rblock * blockSize + table[blockTypes[rblock]][0][r % blockSize + 1]
			]
		];
		return min(left, min(inner, right));
	}

public:
	RMQ(vector<int> array)
	{
		this->array = array;
		buildYourself();
	}

	vector<int> getDepths()
	{
		return depths;
	}

	vector<int> getVertices()
	{
		return vertices;
	}

	Pnode getTree()
	{
		return tree;
	}

	void printCartesian(Pnode T)
	{
		if (T == NULL)
			return;
		printCartesian(T->l);
		printf("%d %d\n", T->x, T->y);
		printCartesian(T->r);
	}

	int getRMQ(int l, int r)
	{
		int l1 = first[l];
		int r1 = first[r];
		if (l1 > r1)
			swap(l1, r1);
		return rmq(l1, r1);
	}
};