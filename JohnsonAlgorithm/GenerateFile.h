#pragma once

#include <fstream>
#include <random>


int generateFile() {
    const int numVertices = 500;
    const int numEdges = 5000;
    const int maxWeight = 100;

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_vertex(1, numVertices);
    std::uniform_int_distribution<> dis_weight(1, maxWeight);

    // Create a vector to store edges
    std::vector<std::pair<int, int>> edges;

    // Generate random edges
    while (edges.size() < numEdges) {
        int from = dis_vertex(gen);
        int to = dis_vertex(gen);

        if ((edges.size() > 0 && from != to && std::make_pair(std::min(from, to), std::max(from, to)) != edges.back()) || edges.size() == 0)
        {
            edges.emplace_back(from, to);
        }
    }

    // Shuffle the edges
    std::shuffle(edges.begin(), edges.end(), gen);

    // Open the output file
    std::ofstream outputFile("input.txt");
    if (!outputFile.is_open()) {
        std::cout << "Failed to open output file." << std::endl;
        return 1;
    }

    // Write the number of vertices and edges to the file
    outputFile << numVertices << " " << numEdges << std::endl;

    // Write the edges to the file
    for (const auto& edge : edges) {
        int weight = dis_weight(gen);
        outputFile << edge.first << " " << edge.second << " " << weight << std::endl;
    }

    outputFile.close();

    std::cout << "Input data written to 'input.txt'" << std::endl;

    return 0;
}