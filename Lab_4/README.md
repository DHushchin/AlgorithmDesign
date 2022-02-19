## Vertex cover problem 

(300 vertices, the degree of the vertex is not more than 30, but not less than 2).

The vertex coverage for an undirected graph G = (V, E) is the set of its vertices S such that, at each edge of the graph at least one end enters the vertex with S. The problem of vertex coverage is to find the vertex coverage of the smallest size for a given graph (this size is called the number of vertex coverage of the graph). 

**At the input**: Graph G = (V, E). 

**Result**: the set C ⊆ V is the smallest vertex coverage of the graph G. 

**Application**:
- location of service points;
- appointment of crews for transport;
- design of integrated circuits and conveyor lines.

## Algorithms and investigated parameters
**Genetic algorithm**:
- crossing operator (minimum 3);
- mutation (minimum 2);
- local improvement operator (minimum 2).