#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <stack>

#define int long long

using namespace std;

struct Edge
{
    int from;   // start vertix
    int to;     // final vertix
    int weight;  // weight of edge
};

class Graph
{
private:
    int V;  // amount of vertices
    vector <Edge> edges;  // vector of edges

    vector<vector<pair<int, int>>> adj_list;  // graph adjacency list

    vector <int> BellmanFord(int& V, vector <Edge> edges)
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
        vector <int> dist(V + 1, LLONG_MAX);
        dist[0] = 0;

        for (int i = 1; i < V; i++)
            for (auto e : edges)
                if (dist[e.from] != LLONG_MAX && dist[e.to] > dist[e.from] + e.weight) dist[e.to] = dist[e.from] + e.weight;

        // the shortest distance values are values of h[]
        return dist;
    }

    // Dijkstra Algorithm
    vector<int> Dijkstra(int src, vector<vector<pair<int, int>>>& adj_list, int V, vector<vector<int>>& pathes)
    {
        vector<int> dist(V + 1, numeric_limits<int>::max());
        dist[src] = 0;

        // initialize the Fibonacci heap
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, src });

        // initialize the parent array to track the shortest path
        vector<int> parent(V + 1, -1);
        parent[src] = src;

        while (!pq.empty())
        {
            int f = pq.top().second;
            pq.pop();

            for (const auto& u : adj_list[f])
            {
                int s = u.first;
                int w = u.second;
                if (dist[f] + w < dist[s])
                {
                    dist[s] = dist[f] + w;
                    parent[s] = f;  // update the parent vertex
                    pq.push({ dist[s], s });
                }
            }
        }

        pathes[src] = parent;

        return dist;
    }

public:

    Graph(vector<Edge>& edges, int V) : edges(edges), V(V)
    {
        adj_list.resize(V + 1);
        for (const auto& edge : edges)
            adj_list[edge.from].emplace_back(edge.to, edge.weight);
    }

    void print_graph()
    {
        for (int i = 1; i <= V; ++i) {
            cout << "Vertex " << i << ": ";
            for (const auto& neighbor : adj_list[i]) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
        cout << endl;
    }

    vector <vector<int>> Johnson(int E, vector<vector<int>>& pathes)
    {
        // the shortest distance values are values of h[]
        vector <int> h = BellmanFord(V, edges);

        for (const Edge& edge : edges) {
            if (h[edge.from] != LLONG_MAX && h[edge.to] > h[edge.from] + edge.weight) {
                cout << "The graph contains a cycle with negative weight." << endl;
                return vector <vector<int>>(); // return empty vector
            }
        }

        for (int i = 0; i < E; i++)
        {
            int u = edges[i].from;
            int v = edges[i].to;
            // for every pair of vertices u and v, having an edge (u -> v), add h[u] - h[v] to the edge weight.
            edges[i].weight += (h[u] - h[v]);
        }

        /*
            2D matrix to store all-pairs shortest path
            path[u][v] = shortest path from u to v
        */
        vector <vector<int>> path(V + 1, vector <int>(V + 1, LLONG_MAX));


        /*
        Step 4 - Remove the added vertex (vertex 0) and apply Dijkstra's algorithm for every vertex.
        */
        for (int i = 1; i <= V; i++)
            path[i] = Dijkstra(i, adj_list, V, pathes);

        return path;
    }
};


signed main() {
    // vertices, edges
    int V, E, from, to, weight, src;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    /*
        vector to store edges
        edge - (from->to)
        weight - weight
        edges.push_back({from, to, weight})
    */
    vector<Edge> edges;
    cout << "Enter the edges in 'from to weight' format:\n";
    for (int i = 0; i < E; ++i)
    {
        cin >> from >> to >> weight;
        edges.push_back({from, to, weight});
    }

    Graph g(edges, V);

    g.print_graph();

    // shortest paths
    vector<vector<int>> pathes(V + 1);

    // weight of shortest paths
    vector<vector<int>> all_distances = g.Johnson(E, pathes);

    // if graph has negative cycle
    if (all_distances == vector<vector<int>>()) return 0;

    // user can choose vertex for which result would be displayed
    while (true)
    {
        cout << "Enter the vertex number to display the shortest paths: ";
        cin >> src;
        if (src == 0) break;
        if (src <= 0 || src > V) cout << "Invalid vertex number." << endl;
        else
        {
            for (int i = 1; i <= V; ++i)
            {
                if (all_distances[src][i] == LLONG_MAX) cout << "The path to the vertex " << i << " does not exist." << endl;
                else
                {
                    cout << src << " <-> " << i << " weight: " << all_distances[src][i] << " path: ";
                    // print the shortest path vertices
                    stack <int> path;
                    int v = i;
                    while (v != src)
                    {
                        path.push(v);
                        v = pathes[src][v];
                    }
                    path.push(src);

                    while (!path.empty())
                    {
                        cout << path.top();
                        path.pop();
                        if (!path.empty()) cout << "->";
                    }
                    cout << endl;
                }
            }
        }
        cout << endl;
    }

    return 0;
}