#include "GraphS.h"

/// <summary>
/// Johnson's algorithm without multithreading
/// </summary>
/// <param name="E">Number of edges</param>
/// <param name="paths">Pathes from each vertex to each vertex</param>
/// <returns>Distances(weight) of the shortest paths</returns>
std::vector<std::vector<lng>> GraphS::Johnson(lng E, std::vector<std::vector<lng>>& paths) 
{
    // Start time measurement
    auto start_time = std::chrono::high_resolution_clock::now();

    // the shortest distance values are values of h[]
    std::vector<lng> h = BellmanFord(V, edges);

    // Check for negative weight cycle
    for (const Edge& edge : edges) 
    {
        if (h[edge.from] != LLONG_MAX && h[edge.to] > h[edge.from] + edge.weight) 
        {
            std::cout << "The graph contains a cycle with negative weight." << std::endl;
            return std::vector<std::vector<lng>>(); // return empty vector
        }
    }

    // Update edge weights
    for (int i = 0; i < E; i++) 
    {
        lng u = edges[i].from;
        lng v = edges[i].to;
        edges[i].weight += (h[u] - h[v]);
    }

    /*
        2D matrix to store all-pairs shortest path
        path[u][v] = shortest path from u to v
    */
    std::vector<std::vector<lng>> path(V + 1, std::vector<lng>(V + 1, LLONG_MAX));

    /*
    Step 4 - Remove the added vertex (vertex 0) and apply Dijkstra's algorithm for every vertex.
    */
    for (int i = 1; i <= V; i++)
        path[i] = Dijkstra(i, adj_list, V, paths);

    // End time measurement
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Execution time (OldGraphRealization): " << duration << " microseconds" << std::endl;

    return path;
}