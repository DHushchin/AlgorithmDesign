#include "GeneticAlgorithm.h"

using namespace std;

GenAlgo::GenAlgo(Graph other)
{
	this->graph = other;
	this->solutions = vector<vector<int>>();
	for (int i = 0; i < 100; i++)
	{
		RandCover Cover(graph);
		this->solutions.push_back(Cover.Solve());

	}
}
