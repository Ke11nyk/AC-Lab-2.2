#include "pch.h"
#include <fstream>
#include <vector>
#include "..\JohnsonAlgorithm\Edge.h"
#include "..\JohnsonAlgorithm\GraphS.h"
#include "..\JohnsonAlgorithm\GraphMT.h"


TEST(GraphSJohnsonAlgorithmTest, NotNegativeCycle)
{
    int V = 3, E = 2;
    std::vector<Edge> edges;

    edges.push_back({ 1, 2, 3 });
    edges.push_back({ 2, 3, 4 });

    // Create instances of both realizations
    GraphS graphS(edges, V);

    // shortest paths
    std::vector<std::vector<lng>> paths(V + 1);
    std::vector<std::vector<lng>>& distances = graphS.Johnson(E, paths);

    // if graph has negative cycle
    EXPECT_FALSE(distances.empty());
    
    EXPECT_EQ(distances[1][1], 0);
    EXPECT_EQ(distances[1][2], 3);
    EXPECT_EQ(distances[1][3], 7);

    EXPECT_EQ(distances[2][1], LLONG_MAX);
    EXPECT_EQ(distances[2][2], 0);
    EXPECT_EQ(distances[2][3], 4);

    EXPECT_EQ(distances[3][1], LLONG_MAX);
    EXPECT_EQ(distances[3][2], LLONG_MAX);
    EXPECT_EQ(distances[3][3], 0);
}

TEST(GraphSJohnsonAlgorithmTest, NegativeCycle)
{
    int V = 3, E = 3;
    std::vector<Edge> edges;

    edges.push_back({ 1, 2, 1 });
    edges.push_back({ 2, 3, -3 });
    edges.push_back({ 3, 1, 1 });

    // Create instances of both realizations
    GraphS graphS(edges, V);

    // shortest paths
    std::vector<std::vector<lng>> paths(V + 1);
    std::vector<std::vector<lng>>& distances = graphS.Johnson(E, paths);

    // if graph has negative cycle
    EXPECT_TRUE(distances.empty());
}


TEST(GraphMTJohnsonAlgorithmTest, NotNegativeCycle)
{
    int V = 3, E = 2;
    std::vector<Edge> edges;

    edges.push_back({ 1, 2, 3 });
    edges.push_back({ 2, 3, 4 });

    // Create instances of both realizations
    GraphMT graphMT(edges, V, 4);

    // shortest paths
    std::vector<std::vector<lng>> paths(V + 1);
    std::vector<std::vector<lng>>& distances = graphMT.Johnson(E, paths);

    // if graph has negative cycle
    EXPECT_FALSE(distances.empty());

    EXPECT_EQ(distances[1][1], 0);
    EXPECT_EQ(distances[1][2], 3);
    EXPECT_EQ(distances[1][3], 7);

    EXPECT_EQ(distances[2][1], LLONG_MAX);
    EXPECT_EQ(distances[2][2], 0);
    EXPECT_EQ(distances[2][3], 4);

    EXPECT_EQ(distances[3][1], LLONG_MAX);
    EXPECT_EQ(distances[3][2], LLONG_MAX);
    EXPECT_EQ(distances[3][3], 0);
}

TEST(GraphMTJohnsonAlgorithmTest, NegativeCycle)
{
    int V = 3, E = 3;
    std::vector<Edge> edges;

    edges.push_back({ 1, 2, 1 });
    edges.push_back({ 2, 3, -3 });
    edges.push_back({ 3, 1, 1 });

    // Create instances of both realizations
    GraphMT graphMT(edges, V, 4);

    // shortest paths
    std::vector<std::vector<lng>> paths(V + 1);
    std::vector<std::vector<lng>>& distances = graphMT.Johnson(E, paths);

    // if graph has negative cycle
    EXPECT_TRUE(distances.empty());
}