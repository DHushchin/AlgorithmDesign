#include "GeneticAlgorithm.h"

using namespace std;

int GenAlgo::SolutionSize(vector<int>& sol)
{
	int count = 0;
	for (size_t i = 0; i < sol.size(); i++)
	{
		if (sol[i] == 1)
		{
			++count;
		}
	}
	return count;
}

pair<int, vector<int>> GenAlgo::BestSolution()
{
	pair<int, vector<int>> bestSol;
	int minCount = this->tempSolutions[0].second.size();
	for (size_t i = 0; i < this->tempSolutions.size(); i++)
	{
		int count = tempSolutions[i].first;
		if (count < minCount) 
		{
			minCount = count;
			bestSol = this->tempSolutions[i];
		}
	}
	return bestSol;
}

pair<int, vector<int>> GenAlgo::WorstSolution()
{
	pair<int, vector<int>> worstSol;
	int maxCount = 0;
	for (size_t i = 0; i < this->tempSolutions.size(); i++)
	{
		int count = tempSolutions[i].first;
		if (count > maxCount)
		{
			maxCount = count;
			worstSol = this->tempSolutions[i];
		}
	}
	return worstSol;
}

void GenAlgo::ReplaceParents(vector<pair<int, vector<int>>>& children)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i].first < this->WorstSolution().first)
		{
			for (size_t j = 0; j < tempSolutions.size(); j++)
			{
				if (tempSolutions[j].first == this->WorstSolution().first)
				{
					tempSolutions[j] = children[i];
				}
			}
		}
	}
}

void GenAlgo::CorrectChildren(vector<pair<int, vector<int>>>& children)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		VertexCover cover(this->graph);
		if (!cover.isCorrectCover(children[i].second))
		{
			//cover.SolveIncorrect(children[i]);
			children.erase(children.begin() + i);
			--i;
		}
	}
}

void GenAlgo::TournamentSelection(vector<int>& first, vector<int>& second)
{
	first = this->BestSolution().second;
	second = tempSolutions[rand() % tempSolutions.size()].second;
}

void GenAlgo::OnePointCrossover(vector<pair<int, vector<int>>>& children, vector<int>& first, vector<int>& second)
{
	pair<int, vector<int>> firstChild, secondChild;
	for (size_t i = 0; i < first.size() / 2; i++)
	{
		firstChild.second.push_back(first[i]);
		secondChild.second.push_back(second[i]);
	}

	for (int i = first.size() / 2; i < first.size(); i++)
	{
		firstChild.second.push_back(second[i]);
		secondChild.second.push_back(first[i]);
	}
	firstChild.first = this->SolutionSize(firstChild.second);
	secondChild.first = this->SolutionSize(secondChild.second);
	children.push_back(firstChild);
	children.push_back(secondChild);
}

void GenAlgo::TwoPointCrossover(vector<pair<int, vector<int>>>& children, vector<int>& first, vector<int>& second)
{
	pair<int, vector<int>> firstChild, secondChild;
	firstChild.first = secondChild.first = 0;
	for (int i = 0; i < first.size() / 3; i++)
	{
		firstChild.second.push_back(first[i]);
		secondChild.second.push_back(second[i]);
	}

	for (int i = first.size() / 3; i < first.size() * 2/3; i++)
	{
		firstChild.second.push_back(second[i]);
		secondChild.second.push_back(first[i]);
	}

	for (size_t i = first.size() * 2/3; i < first.size(); i++)
	{
		firstChild.second.push_back(first[i]);
		secondChild.second.push_back(second[i]);
	}
	firstChild.first = this->SolutionSize(firstChild.second);
	secondChild.first = this->SolutionSize(secondChild.second);
	children.push_back(firstChild);
	children.push_back(secondChild);
}

void GenAlgo::UniformCrossover(vector<pair<int, vector<int>>>& children, vector<int>& first, vector<int>& second)
{
	pair<int, vector<int>> child;
	child.first = 0;
	for (size_t i = 0; i < children.size(); i++)
	{
		if (rand() % 1)
		{
			child.second.push_back(first[i]);
		}
		else
		{
			child.second.push_back(second[i]);
		}
		if (child.second[child.second.size() - 1] == 1)
		{
			++child.first;
		}
	}
	children.push_back(child);
}

void GenAlgo::BitFlipMutation(vector<pair<int, vector<int>>>& children)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i].second.size())
		{
			int chance = rand() % 100;
			if (chance % 10 == 0)
			{
				pair<int, vector<int>> temp(children[i]);
				int index = rand() % temp.second.size();
				if (temp.second[index] == 0)
				{
					temp.second[index] = 1;
					++temp.first;
				}
				else
				{
					temp.second[index] = 0;
					--temp.first;
				}
				children.push_back(temp);
			}
		}
	}
}

void GenAlgo::SwapMutation(vector<pair<int, vector<int>>>& children)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		int chance = rand() % 100;
		if (chance % 10 == 0) 
		{
			pair<int, vector<int>> temp(children[i]);
			int firstToChange = rand() % temp.second.size();
			int secondToChange;

			do {
				secondToChange = rand() % temp.second.size();
			} while (firstToChange == secondToChange);

			swap(temp.second[firstToChange], temp.second[secondToChange]);
			children.push_back(temp);
		}
	}
}

void GenAlgo::AdjacentImprovement(vector<pair<int, vector<int>>>& children)
{
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		pair<int, vector<int>> temp(children[i]);

		if (temp.first == 0)
		{
			continue;
		}

		for (int j = 0; j < this->graph.getAdjMatrix().size(); j++)
		{
			if (this->graph.getAdjMatrix()[i][j] == 1)
			{
				temp.second[j] = 1;
				break;
			}
		}
		temp.first++;
		children.push_back(temp);
	}
}

void GenAlgo::GreedyImprovement(vector<pair<int, vector<int>>>& children)
{
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		pair<int, vector<int>> temp(children[i]);
		temp.second[this->graph.getMaxDegreeVertex()] = 1;
		temp.first++;
		children.push_back(temp);
	}
}

GenAlgo::GenAlgo(Graph& other)
{
	this->graph = Graph(other);
	this->solutions = vector<pair<int, vector<int>>>();
	this->tempSolutions = vector<pair<int, vector<int>>>();
	this->bestCoverNum = graph.getAdjMatrix().size();
	this->BestCrossover = this->BestMutation = this->BestImprovement = "";
	for (int i = 0; i < 100; i++)
	{
		VertexCover Cover(graph);
		vector<int> sol = Cover.Solve();
		pair<int, vector<int>> temp;
		temp.first = this->SolutionSize(sol);
		temp.second = sol;
		this->solutions.push_back(temp);
	}
	int count = 300;
	for (size_t i = 0; i < solutions.size(); i++)
	{
		if (solutions[i].first < count)
		{
			count = solutions[i].first;
		}
	}
	cout << "Initial solution: " << count << endl;
	this->tempSolutions = vector<pair<int, vector<int>>>(this->solutions);
}

int GenAlgo::Solve(void (GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&),
				   void (GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&), 
				   void (GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&))
{	
	pair<int, vector<int>> bestSol;
	for (int k = 0; k < 1000; k++)
	{
		vector<pair<int, vector<int>>> children;
		vector<int> first, second;
		this->TournamentSelection(first, second);
		(this->*crossoverPtr)(children, first, second);
		(this->*mutationPtr)(children);
		(this->*improvementPtr)(children);
		this->CorrectChildren(children);
		this->ReplaceParents(children);
		bestSol = this->BestSolution();
		if (k % 200 == 0)
		{
			cout << bestSol.first << endl;
		}
	}
	cout << bestSol.first << endl;
	if (bestSol.first < this->bestCoverNum)
	{
		this->bestCoverNum = bestSol.first;
	}
	this->tempSolutions = vector<pair<int, vector<int>>>(this->solutions);
	return bestSol.first;
}


void GenAlgo::TestCrossover(void (GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&),
	                        void (GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&), 
	                        void (GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&))
{
	int best1, best2, best3;
	crossoverPtr = &GenAlgo::OnePointCrossover;
	cout << "One point crossover: ";
	best1 = this->Solve(crossoverPtr, mutationPtr, improvementPtr);

	crossoverPtr = &GenAlgo::TwoPointCrossover;
	cout << "Two point crossover: ";
	best2 = this->Solve(crossoverPtr, mutationPtr, improvementPtr);

	crossoverPtr = &GenAlgo::UniformCrossover;
	cout << "Uniform crossover: ";
	best3 = this->Solve(crossoverPtr, mutationPtr, improvementPtr);

	//int best = min(best1, best2, best3);
	if (best1 <= best2 && best1 <= best3)
	{
		crossoverPtr = &GenAlgo::OnePointCrossover;
		this->BestCrossover = "OnePointCrossover";
	}
	else if (best2 <= best1 && best2 <= best3)
	{
		crossoverPtr = &GenAlgo::TwoPointCrossover;
		this->BestCrossover = "TwoPointCrossover";
	}
	else
	{
		crossoverPtr = &GenAlgo::UniformCrossover;
		this->BestCrossover = "UniformCrossover";
	}
}


void GenAlgo::TestMutation(void (GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&),
	                       void (GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&),
	                       void (GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&))
{
	int best1, best2;
	mutationPtr = &GenAlgo::BitFlipMutation;
	cout << "Bit flip mutation: ";
	best1 = this->Solve(crossoverPtr, mutationPtr, improvementPtr);

	mutationPtr = &GenAlgo::SwapMutation;
	cout << "Swap mutation: ";
	best2 = this->Solve(crossoverPtr, mutationPtr, improvementPtr);


	if (best1 <= best2)
	{
		mutationPtr = &GenAlgo::BitFlipMutation;
		this->BestMutation = "BitFlipMutation";
	}
	else
	{
		mutationPtr = &GenAlgo::SwapMutation;
		this->BestMutation = "SwapMutation";
	}
}


void GenAlgo::TestLocalImprovement(void(GenAlgo::* crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&), void(GenAlgo::* mutationPtr)(vector<pair<int, vector<int>>>&), void(GenAlgo::* improvementPtr)(vector<pair<int, vector<int>>>&))
{
	int best1, best2;
	improvementPtr = &GenAlgo::GreedyImprovement;
	cout << "Greedy improvement: ";
	best1 = this->Solve(crossoverPtr, mutationPtr, improvementPtr);

	improvementPtr = &GenAlgo::AdjacentImprovement;
	cout << "Adjacent improvement: ";
	best2 = this->Solve(crossoverPtr, mutationPtr, improvementPtr);


	if (best1 <= best2)
	{
		improvementPtr = &GenAlgo::BitFlipMutation;
		this->BestImprovement = "GreedyImprovement";
	}
	else
	{
		improvementPtr = &GenAlgo::SwapMutation;
		this->BestImprovement = "AdjacentImprovement";
	}
}


void GenAlgo::TestAlgo()
{
	void (GenAlgo::*crossoverPtr)(vector<pair<int, vector<int>>>&, vector<int>&, vector<int>&) = NULL;
	void (GenAlgo::*mutationPtr)(vector<pair<int, vector<int>>>&) = NULL;
	void (GenAlgo::*improvementPtr)(vector<pair<int, vector<int>>>&) = NULL;
	crossoverPtr = &GenAlgo::OnePointCrossover;
	mutationPtr = &GenAlgo::BitFlipMutation;
	improvementPtr = &GenAlgo::AdjacentImprovement;
	this->TestCrossover(crossoverPtr, mutationPtr, improvementPtr);
	this->TestMutation(crossoverPtr, mutationPtr, improvementPtr);
	this->TestLocalImprovement(crossoverPtr, mutationPtr, improvementPtr);
	cout << endl;
	cout << "Best solution: " << this->bestCoverNum << endl;
	cout << "Best crossover: " << this->BestCrossover << endl;
	cout << "Best mutation: " << this->BestMutation << endl;
	cout << "Best local improvement: " << this->BestImprovement << endl;
}
