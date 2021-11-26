#include <iostream>
#include "GeneticAlgorithm.h"

using namespace std;

int main()
{
    Graph graph;
    graph.fillGraph();
    GenAlgo algo(graph);
    algo.TestAlgo();
    return 0;
}
