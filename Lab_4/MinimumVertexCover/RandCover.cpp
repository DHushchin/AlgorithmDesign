#include "RandCover.h"

using namespace std;


void RandCover::RandEdge(int& firstVertex, int& secondVertex)
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


bool RandCover::isEmpty()
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


RandCover::RandCover(Graph& other)
{
	this->adjMatrix = other.getAdjMatrix();
	this->VertexNumber = other.getVertexNumber();
}


void RandCover::RemoveIncident(int& firstVertex, int& secondVertex)
{
	for (int i = 0; i < this->VertexNumber; i++)
	{
		this->adjMatrix[firstVertex][i] = 0;
		this->adjMatrix[i][firstVertex] = 0;
		this->adjMatrix[secondVertex][i] = 0;
		this->adjMatrix[i][secondVertex] = 0;
	}
}


vector<int> RandCover::Solve()
{
	vector<int> VertexCover;
	while (!this->isEmpty())
	{
		int firstVertex, secondVertex;
		this->RandEdge(firstVertex, secondVertex);
		// add to solution
		VertexCover.push_back(firstVertex);
		VertexCover.push_back(secondVertex);
		this->RemoveIncident(firstVertex, secondVertex);
	}
	return VertexCover;
}
