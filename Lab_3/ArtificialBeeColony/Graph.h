#pragma once
#include <vector>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adjMatrix, ConnectedVertexes;
    vector<int> Colors, Vertexes, Degrees;
    int VertexNumber;
    void addEdge(int&, int&);
    bool isColoringValid(int& vertex);
public:
    Graph();
    void randGraph();
    void printGraph();
    void printColors();
    int getVertexDegree(int& vertex);
    bool graphValidColored();
    bool ColorAndCheck(int&, int&);
    vector<int> getConnectedVertexes(int& vertex);
    int getVertexNumber() const;
    vector<int> getVertexes();
    void resetColors();
};

