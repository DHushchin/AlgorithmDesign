#pragma once
#include "Matrix.hpp"

using namespace std;

class Node {
private:
	enum class State 
	{
		opened, closed
	};

	State state;
	int depth;
	Matrix board;

public:
	Node();
};

