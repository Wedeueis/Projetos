#include "disjointset.h"
#include <iostream>

DisjointSet::DisjointSet(): elements(0), sets(0) {

}

DisjointSet::~DisjointSet() {
	for(int i=0; i<nodes.size(); i++) delete nodes[i];
	nodes.clear();
}

node* DisjointSet::MakeSet(int i) {
	if (elements + 1 > nodes.size()) nodes.push_back(new node);

	nodes[elements]->parent = nodes[elements];
	nodes[elements]->i = i;
	nodes[elements]->rank = 0;

	elements++;
	sets++;

	return nodes[elements-1];
}

node* DisjointSet::Find(node* a) {
	if (a->parent == a) return a;
	else {
		a->parent = Find(a->parent);
		return a->parent;
	}
}

void DisjointSet::Union(node* a0, node* a1) {
	if (a0 == a1) return;

	node *a2 = Find(a0);
	node *a3 = Find(a1);

	if (a2 == a3) return;

	if      (a2->rank < a3->rank) a2->parent = a3;
	else if (a3->rank < a2->rank) a3->parent = a2;
	else {
		a2->parent = a3;
		a3->rank++;
	}

	sets--;
}

int DisjointSet::ElementCount() {
	return elements;
}

int DisjointSet::SetCount() {
	return sets;
}

int DisjointSet::Reduce() {
	int j = 1;
	for (int i = 0; i < elements; i++)
		if (nodes[i]->parent == nodes[i])
			nodes[i]->i = j++;
	return j;
}

void DisjointSet::Reset() {
	elements = sets = 0;
}

std::vector<node*> DisjointSet::getNodes() {
	return nodes;
}