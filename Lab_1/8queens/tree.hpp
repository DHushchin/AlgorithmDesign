#pragma once
#include "node.hpp"
#include <string>

using namespace std;

class Tree
{
private:
	Node node;
	Node* children;
	int limit;
public:
	Tree();
	void expand();
};