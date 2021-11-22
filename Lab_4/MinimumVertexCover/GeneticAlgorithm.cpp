#include "GeneticAlgorithm.h"

using namespace std;

vector<int> GenAlgo::bestSolution()
{
	vector<int> bestSol;
	int minCount = this->solutions[0].size();
	for (size_t i = 1; i < this->solutions.size(); i++)
	{
		int count = 0;
		for (size_t j = 0; j < this->solutions[i].size(); j++)
		{
			if (this->solutions[i][j] == 1)
			{
				++count;
			}
		}
		if (count < minCount) 
		{
			minCount = count;
			bestSol = this->solutions[i];
		}
	}
	return bestSol;
}

void GenAlgo::TournamentSelection(vector<int>& first, vector<int>& second)
{
	first = this->bestSolution();
	do
	{
		second = solutions[rand() % solutions.size()];
	} while (first == second);
}

GenAlgo::GenAlgo(Graph& other)
{
	this->graph = Graph(other);
	this->solutions = vector<vector<int>>();
	for (int i = 0; i < 100; i++)
	{
		RandCover Cover(graph);
		this->solutions.push_back(Cover.Solve());
	}
}

void GenAlgo::Solve()
{
	vector<int> first, second;
	this->TournamentSelection(first, second);
}
