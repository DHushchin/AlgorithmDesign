#pragma once
#include "RandCover.h"
#include <iostream>

using namespace std;

class GenAlgo
{
private:
	vector<vector<int>> solutions;
	Graph graph;
public:
	GenAlgo(Graph other);
};
