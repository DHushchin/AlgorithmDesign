#pragma once
#include "Graph.h"

using namespace std;

class RandCover
{
private:
	vector<vector<int>> adjMatrix;
	int VertexNumber;
	vector<int> VertexCover;
private:
	bool isEmpty();
	void RandEdge(int& firstVertex, int& secondVertex);
	void RemoveIncident(int& vertex);
	void RemoveIncident(int& firstVertex, int& secondVertex);
public:
	RandCover(Graph& other);
	vector<int> Solve();
	bool isCorrectCover(vector<int> solution);
};

