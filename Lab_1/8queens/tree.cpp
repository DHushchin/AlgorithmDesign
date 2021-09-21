#include "Tree.hpp"
#include <queue>
#include <algorithm>
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
			if (LDFS(node->getChildren()[elem], limit))
			{
				return true;
			}
		}
	}
	return false;
}

void Tree::AStar()
{
	
	priority_queue <Node*, vector<Node*>, mycompare> opened;
	//typedef std::priority_queue<Node*, std::vector<Node*>, mycomparison> pq;
	//pq opened(mycomparison(true));
	vector<Board> closed;
	opened.push(root);
	while (!opened.empty())
	{
		opened.top()->getBoard().print();
		cout << "Depth: " << opened.top()->getDepth() << endl;

		if (opened.top()->IsSolved())
		{
			opened.top()->getBoard().print();
			cout << "Depth: " << opened.top()->getDepth() << endl;
			break;
		}

		closed.push_back(opened.top()->getBoard());
		opened.top()->expand();
		vector<Node*> temp = opened.top()->getChildren();
		opened.pop();
		for (size_t i = 0; i < temp.size(); i++)
		{
			for (size_t j = 0; j < closed.size(); j++)
			{
				if (temp[i]->getBoard() == closed[j])
				{
					continue;
				}
			}
			
			opened.push(temp[i]);
		}
	}
}
