#pragma once
#include "VertexCover.h"
#include <iostream>
#include <algorithm>

using namespace std;

class GenAlgo
{
private:
	vector<pair<int, vector<int>>> solutions, tempSolutions;
	int bestCoverNum;
	Graph graph;
	string BestCrossover, BestMutation, BestImprovement;
private:
	int SolutionSize(vector<int>& sol);
	pair<int, vector<int>> BestSolution();
	pair<int, vector<int>> WorstSolution();
	void ReplaceParents(vector<pair<int, vector<int>>>& children);
	void CorrectChildren(vector<pair<int, vector<int>>>& children);
	// selection
	void TournamentSelection(vector<int>& first, vector<int>& second);
	// crossover
	void OnePointCrossover(vector<pair<int, vector<int>>>& children, vector<int>& first, vector<int>& second);
	void TwoPointCrossover(vector<pair<int, vector<int>>>& children, vector<int>& first, vector<int>& second);
	void UniformCrossover(vector<pair<int, vector<int>>>& children, vector<int>& first, vector<int>& second);
	// mutation
	void BitFlipMutation(vector<pair<int, vector<int>>>& children);
	void SwapMutation(vector<pair<int, vector<int>>>& children);
	// local improvement
	void AdjacentImprovement(vector<pair<int, vector<int>>>& children);
	void GreedyImprovement(vector<pair<int, vector<int>>>& children);
	// solution
	int Solve(void (GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&),
		      void (GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&),
		      void (GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&));
	// tests
	void TestCrossover(void (GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&),
		               void (GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&),
		               void (GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&));
	void TestMutation(void (GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&),
		              void (GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&),
		              void (GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&));
	void TestLocalImprovement(void (GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&),
		                       void (GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&),
		                       void (GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&));
public:
	GenAlgo(Graph& other);
	void TestAlgo();
};
