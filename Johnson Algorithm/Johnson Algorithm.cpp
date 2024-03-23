#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <stack>

#define int long long

using namespace std;

struct Edge
{
    int from;   // початкова вершина
    int to;     // кінцева вершина
    int weight;  // вага ребра
};

class Graph
{
public:
    int V;  // кількість вершин
    vector <Edge> edges;  // вектор ребер

    vector<vector<pair<int, int>>> adj_list;  // список суміжності графа

    Graph(vector<Edge>& edges, int V) : edges(edges), V(V)
    {
        adj_list.resize(V + 1);
        for (const auto& edge : edges)
            adj_list[edge.from].emplace_back(edge.to, edge.weight);
    }

    void print_graph()
    {
        for (int i = 1; i <= V; ++i) {
            cout << "Vertice " << i << ": ";
            for (const auto& neighbor : adj_list[i]) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
        cout << endl;
    }

    vector <int> bellmanFord(int& V, vector <Edge> edges)
    {
        /*
            Step 1 - Add a new vertex 0 to the given graph, add edges of
            weight 0 from the new vertex to all the existing vertices.
            edge = {0, u, 0} (1 <= u <= N)
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
        
        //The shortest distance values are values of h[].
        return dist;
    }

    // Dijkstra Algorithm
    vector<int> Dijkstra(int src, vector<vector<pair<int, int>>>& adj_list, int V, vector<vector<int>>& pathes)
    {
        vector<int> dist(V + 1, numeric_limits<int>::max());
        dist[src] = 0;

        // Ініціалізуємо піраміду Фібоначчі
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, src });

        // Initialize the parent array to track the shortest path
        vector<vector<int>> p(V + 1);
        //p[src] = src;

        // Initialize the parent array to track the shortest path
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
                    parent[s] = f;  // Update the parent vertex
                    pq.push({ dist[s], s });
                }
            }
        }

        pathes[src] = parent;

        return dist;
    }

    vector <vector<int>> Johnson(int E, vector<vector<int>>& pathes)
    {
        // The shortest distance values are values of h[].
        vector <int> h = bellmanFord(V, edges);

        for (const Edge& edge : edges) {
            if (h[edge.from] != LLONG_MAX && h[edge.to] > h[edge.from] + edge.weight) {
                cout << "The graph contains a cycle with negative weight." << endl;
                return vector <vector<int>>(); // Повертаємо порожній вектор
            }
        }

        for (int i = 0; i < E; i++)
        {
            int u = edges[i].from;
            int v = edges[i].to;
            //For every pair of vertices u and v, having an edge (u -> v), add h[u] - h[v] to the edge weight.
            edges[i].weight += (h[u] - h[v]);
        }
        /*
            2D matrix to store all-pairs shortest path
            path[u][v] = shortest path from u to v
        */
        vector <vector<int>> path(V + 1, vector <int>(V + 1, INT_MAX));


        /*
        Step 4 - Remove the added vertex (vertex 0) and apply Dijkstra's algorithm for every vertex.
        */
        for (int i = 1; i <= V; i++)
            path[i] = Dijkstra(i, adj_list, V, pathes);

        return path;
    }
};





signed main() {
    //vertices, edges
    int V, E, from, to, weight, src;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;
    /*
        vector to store edges
        edge - (u->v)
        weight - w
        edges.push_back({u, v, w})
    */
    vector<Edge> edges;
    cout << "Enter the edges in 'from to weight' format:\n";
    for (int i = 0; i < E; ++i)
    {
        cin >> from >> to >> weight;
        edges.push_back({ from, to, weight });
    }

    vector<vector<int>> pathes(V + 1);

    Graph g(edges, V);

    g.print_graph();

    // Виклик алгоритму Джонсона
    vector<vector<int>> all_distances = g.Johnson(E, pathes);

    if (all_distances == vector<vector<int>>()) return 0;

    // Дозволяє користувачу обрати вершину та вивести результат
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
                    // Print the shortest path vertices
                    stack <int> path;
                    int v = i;
                    while (v != src)
                    {
                        if (pathes[src][v] == -1) break;
                        path.push(v);
                        v = pathes[src][v];
                    }
                    if (pathes[src][v] != -1) path.push(src);

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
    }

    return 0;
}