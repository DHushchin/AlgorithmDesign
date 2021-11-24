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
	// crossover
	void OnePointCrossover(vector<vector<int>>& children, vector<int>& first, vector<int>& second);
	void ThreePointCrossover(vector<vector<int>>& children, vector<int>& first, vector<int>& second);
	void UniformCrossover(vector<vector<int>>& children, vector<int>& first, vector<int>& second);
	// mutation
	void BitFlipMutation(vector<vector<int>>& children);
	void SwapMutation(vector<vector<int>>& children);
	// local improvement
public:
	GenAlgo(Graph& other);
	void Solve();
};
