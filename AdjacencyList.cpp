//
// Created by max on 7/17/2023.
//

#include "AdjacencyList.h"

// Initializes map for link names and numbers
AdjacencyList::AdjacencyList() {
    links.emplace("google.com", 1);
    links.emplace("gmail.com", 2);
    links.emplace("facebook.com", 3);
    links.emplace("maps.com", 4);
    links.emplace("ufl.edu", 5);
}

// Adds edges from vertex f to vertex t
void AdjacencyList::addEdge(const string& f, const string& t) {
    // No loops allowed
    if (f == t)
        return;
    // Add new vertex
    node temp;
    temp.rank = 1.0f;
    temp.pos = f;
    r_t.emplace(f, temp);
    temp.pos = t;
    r_t.emplace(t, temp);
    // Add from into adjacency list for to
    inDeg[t].push_back(f);
    outDeg[f].push_back(t);
}

// Calculate ranks at time t = 0, r(0)
void AdjacencyList::r_tInitializer() {
    // Each rank is set to 1/|V|
    for (auto& it : r_t)
        it.second.rank = 1.0f / (float)r_t.size();
}

// Create the matrix for multiplication (implemented like adjacency list with nodes)
void AdjacencyList::matrixInitializer() {
    // Each vertex is given a vector with the size of the number of in-degrees it has
    for (const auto& it: inDeg) {
        vector<node> temp(it.second.size());
        matrix.emplace(it.first, temp);
    }
    //
    for (const auto& it: matrix) {
        // Build the matrix
        for (int i = 0; i < it.second.size(); i++) {
            // Rank is determined by the number of out-degrees a vertex's adjacent vertices have
            matrix[it.first][i].rank = 1.0f / (float)outDeg[inDeg[it.first][i]].size();
            // Position is determined by the
            matrix[it.first][i].pos = inDeg[it.first][i];
        }
    }
}
// Calculate and print page ranks for p power iterations
void AdjacencyList::PageRank(int p) {
    // Print r(0) if p = 1 for 1 power iteration, rounded to two decimal places
    if (p == 1) {
        for (const auto& it : r_t)
            cout << setprecision(2) << fixed << it.first << " " << it.second.rank << endl;
    }
    // Otherwise the matrices are multiplied together for p power iterations
    else {
        // Map for final ranks
        map<string ,node> m = r_t;
        // Iterates p - 1 times because r(0) is already calculated
        for (int i = 0; i < p - 1; i++) {
            for (auto& it : m)
                it.second.rank = 0.0f;
            for (auto& it: matrix) {
                float sum = 0.0;
                // Matrices (stored like adjacency lists) are multiplied together using positions
                for (auto& j : it.second) {
                    sum += r_t[j.pos].rank * j.rank;
                }
                // Sums of multiplication are added to m as the page ranks
                m[it.first].rank += sum;
            }
            // Calculated ranks are stored in r_t for more iterations
            for (auto& it : r_t) {
                it.second.rank = m[it.first].rank;
            }
        }
        // Final ranks are printed and rounded to two decimal places
        for (auto& it : r_t)
            cout << setprecision(2) << fixed << it.first << " " << it.second.rank << endl;
    }
}
