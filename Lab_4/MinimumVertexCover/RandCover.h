#pragma once
#include "Graph.h"

using namespace std;

class RandCover
{
private:
	vector<vector<int>> adjMatrix;
	int VertexNumber;
private:
	bool isEmpty();
	void RandEdge(int& firstVertex, int& secondVertex);
	void RemoveIncident(int& firstVertex, int& secondVertex);
public:
	RandCover(Graph& other);
	vector<int> Solve();
};

