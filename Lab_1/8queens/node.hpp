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
	bool isSolved;
public:
	Node();
	Board getBoard();
	void changeState();
};

