#pragma once
#include "RandCover.h"
#include <iostream>

using namespace std;

class GenAlgo
{
private:
	vector<vector<int>> solutions;
	Graph graph;
	vector<int> bestSolution();
	void TournamentSelection(vector<int>& first, vector<int>& second);
public:
	GenAlgo(Graph& other);
	void Solve();
};
