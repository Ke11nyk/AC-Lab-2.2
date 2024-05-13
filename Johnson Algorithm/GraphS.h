#pragma once
#include "Graph.h"

/// <summary>
/// Realization of graph without multithreading
/// </summary>
class GraphS : public Graph {
public:
    GraphS(std::vector<Edge>& edges, lng V) : Graph(edges, V) {}

    std::vector<std::vector<lng>> Johnson(lng E, std::vector<std::vector<lng>>& paths) override;
};