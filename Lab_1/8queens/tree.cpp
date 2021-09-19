#include "Tree.hpp"

using namespace std;

Tree::Tree()
{
	limit = 1;
	children = vector<Node>(56);
}

void Tree::expand()
{	
	for (int i = 0; i < this->node.getBoard().getSize(); i++)
	{
		for (int j = 0; j < this->node.getBoard().getSize() - 1; j++)
		{
			children[i * j + j] = Node(this->node);
			children[i * j + j].getBoard().moveFigure(i);
		}
	}
}

Node Tree::getNode()
{
	return this->node;
}

void Tree::IDS()
{
}
