#pragma once
#include "Graph.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

class ABCAlgorithm
{
private:
	vector<int> AllColors, UsedColors, availableVertexes;
	Graph graph;
	int employed, onlookers;
	mt19937 randomMachine;	
private:
	vector<double> getNectarValues(vector<int>& selectedVertexesDegrees);
	vector<int> sendEmployedBees();
	void sendOnlookerBees(vector<int>& selectedVertexes);
	vector<int> getOnlookerBeesSplit(vector<int>& selectedVerticesDegrees);
	void colorConnectedVertexes(vector<int>& connectedVertexes, int& onlookerBeesCount);
	void colorVertex(int& vertex);
	int getNextColor();
	void resetAlgorithm();
public:
	ABCAlgorithm(Graph&);
	int calculateChromaticNumber();
	void test();
};
