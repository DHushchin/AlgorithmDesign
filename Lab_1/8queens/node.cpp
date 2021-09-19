#include "Node.hpp"

using namespace std;

Node::Node()
{
	state = State::opened;
	depth = 1;
	board.generateQueens();
	this->isSolved = !(this->board.conflictNumber());
}

Node::Node(Node& other)
{
	this->state = State::opened;
	this->depth = other.depth + 1;
	this->board = Board(other.board);
}

void Node::changeState()
{
	state = State::closed;
}
