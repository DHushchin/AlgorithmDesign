#pragma once
#include "Node.hpp"
#include <string>
#include <vector>

using namespace std;

class Tree
{
private:
	Node* root;
	bool LDFS(Node* root, int& depthLimit);
public:
	Tree();
	Node* getRoot();
	void IDS();
	void AStar();
};