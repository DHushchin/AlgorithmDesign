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
	Node(Node& other);
	void changeState();
public:
    State getState() const { return state; }
    void setState(State state) { this->state = state; }

    int getDepth() const { return depth; }
    void setDepth(int depth) { this->depth = depth; }

    Board getBoard() const { return board; }
    void setBoard(Board board) { this->board = board; }

    bool getIsSolved() const { return isSolved; }
    void setIsSolved(bool isSolved) { this->isSolved = isSolved; }
};
