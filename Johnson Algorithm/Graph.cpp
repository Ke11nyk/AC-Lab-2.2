#include "Graph.h"

/// <summary>
/// Bellman-Ford algorithm
/// </summary>
/// <param name="V">Number of vertices</param>
/// <param name="edges">Vector with edges of graph</param>
/// <returns>Distance(weight) of the shortest path</returns>
std::vector<lng> Graph::BellmanFord(lng& V, std::vector<Edge>& edges)
{
    /*
        Step 1 - Add a new vertex 0 to the given graph, add edges of
        weight 0 from the new vertex to all the existing vertices.
        edge = {0, u, 0} (1 <= u <= V)
    */
    for (int i = 1; i <= V; i++)
        edges.push_back({ 0, i, 0 });

    /*
        Step 2 - Find the shortest path from the new vertex to all the other
        existing vertices using the Bellman-Ford algorithm.
    */
    std::vector<lng> dist(V + 1, LLONG_MAX);
    dist[0] = 0;

    for (int i = 1; i < V; i++)
        for (auto e : edges)
            if (dist[e.from] != LLONG_MAX && dist[e.to] > dist[e.from] + e.weight)
                dist[e.to] = dist[e.from] + e.weight;

    // the shortest distance values are values of h[]
    return dist;
}

/// <summary>
/// Dijkstra's algorithm
/// </summary>
/// <param name="src">Index of current vertex</param>
/// <param name="adj_list">Graph adjacency list</param>
/// <param name="V">Number of vertices</param>
/// <param name="paths">Vector of the shortest pathes</param>
/// <returns>Distance(weight) of the shortest path</returns>
std::vector<lng> Graph::Dijkstra(lng src, std::vector<std::vector<std::pair<lng, lng>>>& adj_list, 
    lng V, std::vector<std::vector<lng>>& paths)
{
    std::vector<lng> dist(V + 1, std::numeric_limits<lng>::max());
    dist[src] = 0;

    // initialize the Fibonacci heap
    std::priority_queue<std::pair<lng, lng>, std::vector<std::pair<lng, lng>>, std::greater<std::pair<lng, lng>>> pq;
    pq.push({ 0, src });

    // initialize the parent array to track the shortest path
    std::vector<lng> parent(V + 1, -1);
    parent[src] = src;

    while (!pq.empty()) {
        lng f = pq.top().second;
        pq.pop();

        for (const auto& u : adj_list[f]) {
            int s = u.first;
            int w = u.second;
            if (dist[f] + w < dist[s]) {
                dist[s] = dist[f] + w;
                parent[s] = f; // update the parent vertex
                pq.push({ dist[s], s });
            }
        }
    }

    paths[src] = parent;

    return dist;
}

/// <summary>
/// Graph output to the console
/// </summary>
void Graph::printGraph() {
    for (int i = 1; i <= V; ++i) {
        std::cout << "Vertex " << i << ": ";
        for (const auto& neighbor : adj_list[i]) {
            std::cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}