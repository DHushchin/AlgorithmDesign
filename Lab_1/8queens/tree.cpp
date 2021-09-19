#include "Tree.hpp"

using namespace std;

Tree::Tree()
{
	limit = 1;
	children = vector<Node*>(56);
}

void Tree::expand()
{	
	/*
	for (size_t i = 0; i < this->node.getBoard().getSize(); i++)
	{
		for (size_t j = 0; j < this->node.getBoard().getSize(); i++)
		{
			
		}
	}
	*/
}

Node Tree::getNode()
{
	return this->node;
}
