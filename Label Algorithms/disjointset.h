#include <vector>

struct node{
	node *parent;
	int i, rank;
};

class DisjointSet {
private:
	std::vector<node *> nodes;
	int elements, sets;
public:
	DisjointSet();
	~DisjointSet();

	node* MakeSet(int i);
	node* Find(node* a);
	void Union(node* a0, node* a1);

	std::vector<node*> getNodes();
	int ElementCount();
	int SetCount();

	int Reduce();
	void Reset();
};