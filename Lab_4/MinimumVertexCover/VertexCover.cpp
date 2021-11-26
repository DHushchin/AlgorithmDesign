#include "VertexCover.h"

using namespace std;


void VertexCover::RandEdge(int& firstVertex, int& secondVertex)
{
	while (true)
	{
		firstVertex = rand() % this->VertexNumber;

		for (int j = 0; j < this->VertexNumber; j++)
		{
			if (this->adjMatrix[firstVertex][j] == 1)
			{
				secondVertex = this->adjMatrix[firstVertex][j];
				return;
			}
		}
	}
}

bool VertexCover::isEmpty()
{
	for (int i = 0; i < VertexNumber; i++)
	{
		for (int j = 0; j < VertexNumber; j++)
		{
			if (adjMatrix[i][j] == 1)
			{
				return false;
			}
		}
	}
	return true;
}

void VertexCover::RemoveIncident(int& vertex)
{
	for (int i = 0; i < this->VertexNumber; i++)
	{
		this->adjMatrix[vertex][i] = 0;
		this->adjMatrix[i][vertex] = 0;
	}
}

void VertexCover::RemoveIncident(int& firstVertex, int& secondVertex)
{
	for (int i = 0; i < this->VertexNumber; i++)
	{
		this->adjMatrix[firstVertex][i] = 0;
		this->adjMatrix[i][firstVertex] = 0;
		this->adjMatrix[secondVertex][i] = 0;
		this->adjMatrix[i][secondVertex] = 0;
	}
}

VertexCover::VertexCover(Graph& other)
{
	this->adjMatrix = other.getAdjMatrix();
	this->VertexNumber = other.getVertexNumber();
	this->Cover = vector<int>();
	for (int i = 0; i < VertexNumber; i++)
	{
		Cover.push_back(0);
	}
}

bool VertexCover::isCorrectCover(vector<int>& solution)
{
	for (int i = 0; i < solution.size(); i++)
	{
		if (solution[i] == 1)
		{
			this->RemoveIncident(i);
		}
	}
	return this->isEmpty();
}

vector<int> VertexCover::Solve()
{
	while (!this->isEmpty())
	{
		int firstVertex, secondVertex;
		this->RandEdge(firstVertex, secondVertex);
		// add to solution
		Cover[firstVertex] = 1;
		Cover[secondVertex] = 1;
		this->RemoveIncident(firstVertex, secondVertex);
	}
	return Cover;
}

void VertexCover::SolveIncorrect(pair<int, vector<int>>& solution)
{
	
	for (int i = 0; i < solution.second.size(); i++)
	{
		if (solution.second[i] == 1)
		{
			this->RemoveIncident(solution.second[i]);
		}
	}
	// lazy algo
	while (!this->isEmpty())
	{
		for (int i = 0; i < this->adjMatrix.size(); i++)
		{
			for (int j = 0; j < this->adjMatrix[i].size(); j++)
			{
				if (this->adjMatrix[i][j] == 1)
				{
					solution.second[j] == 1;
					++solution.first;
					this->RemoveIncident(solution.second[j]);
				}
			}
		}
	}
}
