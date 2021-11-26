#pragma once
#include "Graph.h"

using namespace std;

class VertexCover
{
private:
	vector<vector<int>> adjMatrix;
	int VertexNumber;
	vector<int> Cover;
private:
	bool isEmpty();
	void RandEdge(int& firstVertex, int& secondVertex);
	void RemoveIncident(int& vertex);
	void RemoveIncident(int& firstVertex, int& secondVertex);
public:
	VertexCover(Graph& other);
	vector<int> Solve();
	bool isCorrectCover(vector<int>& solution);
	void SolveIncorrect(pair<int, vector<int>>& solution);
};
