#include "Tree.hpp"

using namespace std;

Tree::Tree()
{
	root = new Node();	
}


Node* Tree::getRoot()
{
	return this->root;
}

void Tree::IDS()
{
	int limit = 1;
	while (!(LDFS(root, limit)))
	{
		++limit;
	}
}

bool Tree::LDFS(Node* node, int& limit)
{
	node->getBoard().print();
	cout << "Depth: " << node->getDepth() << endl;
	cout << "Limit: " << limit << endl;
	cout << "Conflicts: " << node->getBoard().conflictNumber() << endl << endl << endl << endl;


	if (node->IsSolved())
	{
		node->getBoard().print();
		cout << "Depth: " << node->getDepth() << endl;
		cout << "Limit: " << limit << endl;
		return true;
	}
	if (node->getDepth() < limit)
	{
		node->expand();
		for (size_t elem = 0; elem < node->getChildren().size(); elem++)
		{
			if (LDFS(node->children[elem], limit))
			{
				return true;
			}
		}
	}
	return false;
}
