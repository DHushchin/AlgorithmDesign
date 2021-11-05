#include "ABCAlgorithm.h"

using namespace std;

ABCAlgorithm::ABCAlgorithm(Graph& graph)
{
	this->graph = graph;
	this->AllColors = vector<int>();
	this->UsedColors = vector<int>();
	for (int i = 0; i < 100; i++)
		AllColors.push_back(i);
	availableVertexes = this->graph.getVertexes();
    employed = 3;
    onlookers = 22;
}


int ABCAlgorithm::calculateChromaticNumber() 
{
    while (!this->graph.graphValidColored()) {
        vector<int> selectedVertices = this->sendEmployedBees();
		this->sendOnlookerBees(selectedVertices);
    }
	int chromaticNumber = this->UsedColors.size();
	return chromaticNumber;
}


vector<int> ABCAlgorithm::sendEmployedBees()
{
    vector<int> selectedVertexes;
    for (int i = 0; i < this->employed; i++) {
        int randIndex = randomMachine() % this->availableVertexes.size();
        int randVertex = this->availableVertexes[randIndex];
        this->availableVertexes.erase(availableVertexes.begin() + randIndex);
        selectedVertexes.push_back(randVertex);
    }
    return selectedVertexes;
}


void ABCAlgorithm::sendOnlookerBees(vector<int>& selectedVertexes)
{
    vector<int> selectedVertexesDegrees;
    for (int i = 0; i < selectedVertexes.size(); i++)
    {
        selectedVertexesDegrees.push_back(this->graph.getVertexDegree(selectedVertexes[i]));
    }
    vector<int> onlookerBeesSplit = this->getOnlookerBeesSplit(selectedVertexesDegrees);

    for (int i = 0; i < selectedVertexes.size(); i++)
    {
        int onlookerBeesCountForVertex = onlookerBeesSplit[i];
        vector<int> connectedVertexes = this->graph.getConnectedVertexes(selectedVertexes[i]);
        this->colorConnectedVertexes(connectedVertexes, onlookerBeesCountForVertex);
        this->colorVertex(selectedVertexes[i]);
    }
}


vector<int> ABCAlgorithm::getOnlookerBeesSplit(vector<int>& selectedVertexesDegrees)
{
    vector<double> nectarValues = this->getNectarValues(selectedVertexesDegrees);
    int onlookerBeesCount = this->onlookers;

    vector<int> onlookerBeesSplit;
    for (int i = 0; i < nectarValues.size(); i++)
    {
        if (i == nectarValues.size() - 1)
        {
            onlookerBeesSplit.push_back(onlookerBeesCount);
        }
        else
        {
            int onlookerForVertex = int(onlookerBeesCount * nectarValues[i]);
            onlookerBeesCount -= onlookerForVertex;
            onlookerBeesSplit.push_back(onlookerForVertex);
        }
    }

    return onlookerBeesSplit;
}


vector<double> ABCAlgorithm::getNectarValues(vector<int>& selectedVertexesDegrees)
{
    int summarySelectedVertexesDegree = 0;
    for (int i = 0; i < selectedVertexesDegrees.size(); i++)
    {
        summarySelectedVertexesDegree += selectedVertexesDegrees[i];
    }
    vector<double> nectar;
    for (int i = 0; i < selectedVertexesDegrees.size(); i++)
    {
        nectar.push_back(double(selectedVertexesDegrees[i]) / double(summarySelectedVertexesDegree));
    }
    
    return nectar;
}


void ABCAlgorithm::colorConnectedVertexes(vector<int>& connectedVertexes, int& onlookerBeesCount)
{
    for (int i = 0; i < connectedVertexes.size(); i++)
    {
        if (i >= onlookerBeesCount - 1)
        {
            return;
        }
        this->colorVertex(connectedVertexes[i]);
    }
}


void ABCAlgorithm::colorVertex(int& vertex)
{
    vector<int> availableColors(this->UsedColors);
    bool isColoredSuccessfully = false;
    while (!isColoredSuccessfully)
    {
        if (availableColors.size() == 0) 
        {
            int newColor = getNextColor();
            UsedColors.push_back(newColor);
            this->graph.ColorAndCheck(vertex, newColor);
            isColoredSuccessfully = true;
            break;
        }
        int randomColorIndex = randomMachine() % availableColors.size();
        int randomAvailableColor = availableColors[randomColorIndex];
        availableColors.erase(availableColors.begin() + randomColorIndex);
        isColoredSuccessfully = this->graph.ColorAndCheck(vertex, randomAvailableColor);
    }
}


int ABCAlgorithm::getNextColor()
{
    return this->AllColors[this->UsedColors.size()];
}


void ABCAlgorithm::resetAlgorithm()
{
    this->UsedColors.clear(); 
    this->availableVertexes = this->graph.getVertexes();
    this->graph.resetColors();
}


void ABCAlgorithm::test()
{
    int bestRes = this->calculateChromaticNumber();
    Graph res;
    this->resetAlgorithm();
    for (int i = 0; i < 1000; i++) 
    {
        if (i % 20 == 0) 
        {
            cout << "Iteration: " << i << " Result: " << bestRes << endl;
        }
        int newChromaticNumber = this->calculateChromaticNumber();
        if (newChromaticNumber < bestRes) 
        {
            bestRes = newChromaticNumber;
            res = this->graph;
        }
        this->resetAlgorithm();
    }
    res.printColors();
}
