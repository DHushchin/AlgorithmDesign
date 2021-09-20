#pragma once
#include "Node.hpp"
#include <string>
#include <vector>

using namespace std;

class Tree
{
private:
	Node* root;
	
public:
	Tree();
	Node* getRoot();
	void IDS();
	bool LDFS(Node* root, int& depthLimit);
};