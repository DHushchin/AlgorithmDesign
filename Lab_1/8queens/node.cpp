#include "node.hpp"

Node::Node()
{
	state = State::opened;
	depth = 1;
	board = Matrix();
}
