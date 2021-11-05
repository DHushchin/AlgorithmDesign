#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph()
{
    this->VertexNumber = 150;
    this->adjMatrix = vector<vector<int>>(VertexNumber);
    this->Colors = vector<int>(VertexNumber, -1);
    this->Vertexes = vector<int>();
    this->Degrees = vector<int>();
    this->ConnectedVertexes = vector<vector<int>>(VertexNumber);
    for (int i = 0; i < VertexNumber; i++)
    {
        for (int j = 0; j < VertexNumber; j++)
        {
            this->adjMatrix[i].push_back(0);
        }
    }
    this->randGraph();
    for (int i = 0; i < this->VertexNumber; i++)
    {
        this->Vertexes.push_back(i);
        int count = 0;
        for (int j = 0; j < this->VertexNumber; j++)
        {
            if (this->adjMatrix[i][j] == 1)
            {
                ++count;
                this->ConnectedVertexes[i].push_back(j);
            }
        }
        this->Degrees.push_back(count);
    }
}


void Graph::addEdge(int& first, int& second)
{
    if (0 <= first < VertexNumber && 0 <= second < VertexNumber && first != second) 
    {
        adjMatrix[first][second] = 1;
        adjMatrix[second][first] = 1;
        return;
    }
    cout << "Input error!" << endl;
}


void Graph::randGraph() 
{
    srand(time(NULL));
    for (int i = 0; i < VertexNumber; i++) 
    {
        int adjMax = rand() % 30 + 1;
        for (int k = 0; k < VertexNumber; k++)
        {
            if (adjMatrix[i][k] == 1)
            {
                --adjMax;
            }
        }
        for (int j = 0; j < adjMax && i != j; j++) // not more than 30
        {
            int vertex = rand() % VertexNumber;
            if (i != vertex) // can't be adjacent to itself
            {
                addEdge(i, vertex);
            }
        }
    }
}


void Graph::printGraph() 
{
    for (int i = 0; i < VertexNumber; i++) {
        cout << i << ": "; 
        for (int j = 0; j < VertexNumber; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl << endl;
    }
}

void Graph::printColors()
{
    cout << endl;
    for (int i = 0; i < VertexNumber; i++)
    {
        cout << "Vertex " << i << ": " << Colors[i] << "  ";
        if (i % 10 == 0 && i != 0)
            cout << endl;
    }
}


int Graph::getVertexNumber() const
{
    return this->VertexNumber;
}


vector<int> Graph::getVertexes()
{
    return this->Vertexes;
}


bool Graph::graphValidColored()
{
    for (int i = 0; i < Colors.size(); i++)
    {
        if (Colors[i] == -1)
        {
            return false;
        }
    }
    for (int i = 0; i < VertexNumber; i++)
    {
        if (!this->isColoringValid(i))
        {
            return false;
        }
    }
    return true;
}


bool Graph::ColorAndCheck(int& vertex, int& newColor) 
{
    int oldColor = this->Colors[vertex];
    this->Colors[vertex] = newColor;
    bool isValid = this->isColoringValid(vertex);
    if (!isValid) 
    {
        this->Colors[vertex] = oldColor;
    }
    return isValid;
}


bool Graph::isColoringValid(int& vertex)
{
    vector<int> connected = this->getConnectedVertexes(vertex);
    for (int i = 0; i < connected.size(); i++)
    {
        if (this->adjMatrix[vertex][connected[i]] == 1 && // has adjacent
            this->Colors[vertex] != -1 && // first vertex has color
            this->Colors[connected[i]] != -1 && // second vertex has color
            this->Colors[vertex] == this->Colors[connected[i]]) // same colors
        {
            return false;
        }
    }
    return true;
}


int Graph::getVertexDegree(int& vertex)
{
    return this->Degrees[vertex];
}


vector<int> Graph::getConnectedVertexes(int& vertex)
{
    return this->ConnectedVertexes[vertex];
}


void Graph::resetColors()
{
    this->Colors = vector<int>(VertexNumber, -1);
}
