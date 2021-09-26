#pragma once
#include "Node.hpp"
#include <string>
#include <vector>

using namespace std;

class Tree
{
private:
	int memory_states, total_states, iter;
	Node* root;
	bool LDFS(Node* root, int& depthLimit);
public:
	Tree();
	Node* getRoot();
	void IDS();
	void AStar();
};