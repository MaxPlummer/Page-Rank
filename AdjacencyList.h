//
// Created by max on 7/17/2023.
//

#ifndef PAGERANK_ADJACENCYLIST_H
#define PAGERANK_ADJACENCYLIST_H

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <queue>
#include <iterator>
using namespace std;

// Adjacency list class to represent the graph
class AdjacencyList {
private:
    // Object to store a vertex's rank and position in the matrices
    struct node {
        string pos;
        float rank;
    };
    // Map representing the websites and vertex numbers and positions
    map<string, int> links;
    // Map for vertices and ranks
    map<string, node> r_t;
    // Represent graph as adjacency list using maps
    // inDeg map represents vertices (key) and vertices pointing to them (value)
    map<string, vector<string>> inDeg;
    // outDeg map represents vertices (key) and vertices they point to (value)
    map<string, vector<string>> outDeg;
    // Map for matrix M (implemented like an adjacency list)
    map<string, vector<node>> matrix;
public:
    // Constructor
    AdjacencyList();
    // Adds edges from vertex f to vertex t
    void addEdge(const string& f, const string& t);
    // Calculate ranks at time t = 0, r(0)
    void r_tInitializer();
    // Create the matrix for multiplication (implemented like adjacency list with nodes)
    void matrixInitializer();
    // Calculate and print page ranks for p power iterations
    void PageRank(int p);
};

#endif //PAGERANK_ADJACENCYLIST_H
