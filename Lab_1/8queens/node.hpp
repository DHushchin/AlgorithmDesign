#pragma once
#include "Board.hpp"

using namespace std;

class Node {
private:
	int depth;
	Board board;
	vector<Node*> children;

public:
	Node();
	Node(Node& other);
	bool IsSolved();
	void expand();

public:

    int getDepth() const { return depth; }
    void setDepth(int depth) { this->depth = depth; }

    Board getBoard() const { return this->board; }
    void setBoard(Board board) { this->board = board; }

    vector<Node*> getChildren() const { return this->children; }
    void setChildren(vector<Node*> children) { this->children = children; }

};

struct mycompare {
	bool operator()(const Node* first, const Node* second) {
		if (first->getBoard().conflictNumber() != second->getBoard().conflictNumber())
		{
			return first->getBoard().conflictNumber() > second->getBoard().conflictNumber();
		}
		return first->getDepth() > second->getDepth();
	};
};
