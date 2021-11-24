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

void GenAlgo::OnePointCrossover(vector<vector<int>>& children, vector<int>& first, vector<int>& second)
{
	vector<int> firstChild, secondChild;
	for (int i = 0; i < children.size() / 2; i++)
	{
		firstChild.push_back(first[i]);
		secondChild.push_back(second[i]);
	}

	for (int i = children.size() / 2; i < children.size(); i++)
	{
		firstChild.push_back(second[i]);
		secondChild.push_back(first[i]);
	}
	children.push_back(firstChild);
	children.push_back(secondChild);
}

void GenAlgo::ThreePointCrossover(vector<vector<int>>& children, vector<int>& first, vector<int>& second)
{
	vector<int> firstChild, secondChild;
	for (int i = 0; i < children.size() / 3; i++)
	{
		firstChild.push_back(first[i]);
		secondChild.push_back(second[i]);
	}

	for (int i = children.size() / 3; i < children.size() * 2/3; i++)
	{
		firstChild.push_back(second[i]);
		secondChild.push_back(first[i]);
	}

	for (int i = children.size() * 2/3; i < children.size(); i++)
	{
		firstChild.push_back(first[i]);
		secondChild.push_back(second[i]);
	}
	children.push_back(firstChild);
	children.push_back(secondChild);
}

void GenAlgo::UniformCrossover(vector<vector<int>>& children, vector<int>& first, vector<int>& second)
{
	vector<int> child;
	for (int i = 0; i < children.size(); i++)
	{
		if (rand() % 1)
		{
			child.push_back(first[i]);
		}
		else
		{
			child.push_back(second[i]);
		}
	}
	children.push_back(child);
}

void GenAlgo::BitFlipMutation(vector<vector<int>>& children)
{
	for (int i = 0; i < children.size(); i++)
	{
		int chance = rand() % 100;
		if (chance % 10 == 0) 
		{
			int index = rand() % children[i].size();
			if (children[i][index] == 0)
			{
				children[i][index] = 1;
			}
			else
			{
				children[i][index] = 0;
			}
		}
	}
}

void GenAlgo::SwapMutation(vector<vector<int>>& children)
{
	for (int i = 0; i < children.size(); i++)
	{
		int chance = rand() % 100;
		if (chance % 10 == 0) 
		{
			int firstToChange = rand() % children[i].size();
			int secondToChange;

			do {
				secondToChange = rand() % children[i].size();
			} while (firstToChange == secondToChange);

			swap(children[i][firstToChange], children[i][secondToChange]);
		}
	}
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
	vector<vector<int>> children;
	vector<int> first, second;
	this->TournamentSelection(first, second);
	/*TODO: передавать функции как параметры из другого метода*/
}
