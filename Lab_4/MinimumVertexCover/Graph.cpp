#include "Graph.h"
#include <iostream>
#include <fstream>

using namespace std;

Graph::Graph()
{
    this->VertexNumber = 300;
    this->adjMatrix = vector<vector<int>>(VertexNumber);

    for (int i = 0; i < VertexNumber; i++)
    {
        for (int j = 0; j < VertexNumber; j++)
        {
            this->adjMatrix[i].push_back(0);
        }
    }
}

Graph::Graph(Graph& other)
{
    this->VertexNumber = other.VertexNumber;
    this->adjMatrix = vector<vector<int>>(VertexNumber);
    for (int i = 0; i < VertexNumber; i++)
    {
        for (int j = 0; j < VertexNumber; j++)
        {
            this->adjMatrix[i].push_back(other.adjMatrix[i][j]);
        }
    }
}

void Graph::fillGraph()
{
    int option;
    do {
        cout << "Choose option: \n 0 - random generation \n 1 - read from file" << endl << "Option: ";
        cin >> option;
        if (option == 0)
        {
            this->randGraph();
            this->saveGraph();
        }
        else if (option == 1)
        {
            this->readGraph();
        }
        else
        {
            cout << "Incorrect input. Try again!" << endl;
        }
    } while (option < 0 or option > 1);
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
        int adjMax = rand() % 29 + 2; // from 2 to 30
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

void Graph::readGraph()
{
    ifstream file;
    file.open("AdjMatrix.txt");

    for (int i = 0; i < this->VertexNumber; ++i) {
        for (int j = 0; j < this->VertexNumber; ++j) {
            int temp;
            file >> temp;
            this->adjMatrix[i][j] = temp;
        }
    }

    file.close();
}

void Graph::saveGraph()
{
    ofstream file;
    file.open("AdjMatrix.txt");
    for (int i = 0; i < VertexNumber; ++i) {
        for (int j = 0; j < VertexNumber; ++j) {
            file << adjMatrix[i][j] << ' ';
        }
        file << '\n';
    }
    file.close();
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

int Graph::getVertexNumber() const
{
    return VertexNumber;
}

vector<vector<int>> Graph::getAdjMatrix() const
{
    return adjMatrix;
}

int Graph::getMaxDegreeVertex()
{
    pair<int, int> vert;
    vert.first = vert.second = 0;
    for (int i = 0; i < this->adjMatrix.size(); i++)
    {
        int count = 0;
        for (int j = 0; j < this->adjMatrix[i].size(); j++)
        {
            if (this->adjMatrix[i][j] == 1)
            {
                ++count;
            }
        }
        if (count > vert.first)
        {
            vert.first = count;
            vert.second = i;
        }
    }
    return vert.second;
}
