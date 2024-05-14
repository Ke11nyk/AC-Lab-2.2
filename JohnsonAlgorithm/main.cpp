#include <stack>
#include "GraphMT.h"
#include "GraphS.h"
#include "Edge.h"
#include "GenerateFile.h"

int main() {
    generateFile();

    // Open the input file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    inputFile.seekg(0);

    int V, E, from, to, weight;

    // Read the number of vertices and edges
    inputFile >> V >> E;

    /*
        vector to store edges
        edge - (from->to)
        weight - weight
        edges.push_back({from, to, weight})
    */
    std::vector<Edge> edges;

    // Read the edges from the file
    for (int i = 0; i < E; ++i) {
        inputFile >> from >> to >> weight;
        edges.push_back({ from, to, weight });
    }

    inputFile.close(); // Close the input file

    // Create instances of both realizations
    GraphS oldGraph(edges, V);
    GraphMT newGraph(edges, V, 4);

    // Print the graph
    //cout << "Graph:" << endl;
    //oldGraph.print_graph();

    // shortest paths
    std::vector<std::vector<lng>> oldPaths(V + 1), newPaths(V + 1);

    // weight of shortest paths
    std::vector<std::vector<lng>> oldDistances = oldGraph.Johnson(E, oldPaths);
    std::vector<std::vector<lng>> newDistances = newGraph.Johnson(E, newPaths);

    // if graph has negative cycle
    if (oldDistances.empty() || newDistances.empty()) {
        std::cout << "The graph contains a cycle with negative weight." << std::endl;
        return 0;
    }

    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        std::cout << "Choose the realization to display the shortest paths (1 for old, 2 for new, 0 to exit): ";
        std::cin >> choice;

        if (choice == 0) {
            exitProgram = true;
            continue;
        }

        bool exitRealization = false;

        while (!exitRealization) {
            std::cout << "Enter the vertex number to display the shortest paths (0 to go back): ";
            int src;
            std::cin >> src;
            if (src == 0) {
                exitRealization = true;
                continue;
            }
            if (src <= 0 || src > V) std::cout << "Invalid vertex number." << std::endl;
            else {
                std::vector<std::vector<lng>>& distances = (choice == 1) ? oldDistances : newDistances;
                std::vector<std::vector<lng>>& paths = (choice == 1) ? oldPaths : newPaths;

                for (int i = 1; i <= V; ++i) {
                    if (distances[src][i] == LLONG_MAX)
                        std::cout << "The path to the vertex " << i << " does not exist." << std::endl;
                    else {
                        std::cout << src << " <-> " << i << " weight: " << distances[src][i] << " path: ";
                        // print the shortest path vertices
                        std::stack<lng> path;
                        int v = i;
                        while (v != src) {
                            path.push(v);
                            v = paths[src][v];
                        }
                        path.push(src);

                        while (!path.empty()) {
                            std::cout << path.top();
                            path.pop();
                            if (!path.empty()) std::cout << "->";
                        }
                        std::cout << std::endl;
                    }
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}