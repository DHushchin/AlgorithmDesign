#pragma once
#include "Node.hpp"
#include <string>
#include <vector>

using namespace std;

class Tree
{
private:
	Node node;
	vector<Node> children;
	int limit;
public:
	Tree();
	void expand();
	Node getNode();
	void IDS();
};