#pragma once
#include "Board.hpp"

using namespace std;

class Node {
private:

	enum class State
	{
		opened, closed
	};

	State state;
	int depth;
	Board board;
public:
	vector<Node*> children;
	
public:
	Node();
	Node(Node& other);
	void changeState();
	bool IsSolved();
	void expand();

public:
    State getState() const { return state; }
    void setState(State state) { this->state = state; }

    int getDepth() const { return depth; }
    void setDepth(int depth) { this->depth = depth; }

    Board getBoard() const { return this->board; }
    void setBoard(Board board) { this->board = board; }

    vector<Node*> getChildren() const { return this->children; }
    void setChildren(vector<Node*> children) { this->children = children; }

};
