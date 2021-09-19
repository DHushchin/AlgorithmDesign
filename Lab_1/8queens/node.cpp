#include "Node.hpp"

using namespace std;

Node::Node()
{
	state = State::opened;
	depth = 1;
	board.generateQueens();
	//isSolved = this->board.conflictNumber();
}

Board Node::getBoard()
{
	return this->board;
}

void Node::changeState()
{
	state = State::closed;
}
