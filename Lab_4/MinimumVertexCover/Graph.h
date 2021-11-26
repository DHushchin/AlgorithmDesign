#pragma once
#include <vector>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adjMatrix;
    int VertexNumber;
private:
    void addEdge(int&, int&);
    void randGraph();
    void readGraph();
    void saveGraph();
public:
    Graph();
    Graph(Graph& other);
    void fillGraph();
    void printGraph();
    int getVertexNumber() const;
    vector<vector<int>> getAdjMatrix() const;
    int getMaxDegreeVertex();
};

