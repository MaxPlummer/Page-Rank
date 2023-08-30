#include "AdjacencyList.h"

int main() {
    // Create new adjacency list
    AdjacencyList adj;
    // Get input
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;
    for(int i = 0; i < no_of_lines; i++) {
        cin >> from;
        cin >> to;
        // Adds vertices and edges
        adj.addEdge(from, to);
    }
    // Calculate ranks at time t = 0, r(0)
    adj.r_tInitializer();
    // Create the matrix for multiplication (implemented like adjacency list with nodes)
    adj.matrixInitializer();
    // Calculate and print page ranks
    adj.PageRank(power_iterations);
    // Close program
    return 0;
}
