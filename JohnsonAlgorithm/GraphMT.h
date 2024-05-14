#pragma once

#include <thread>
#include <future>
#include <mutex>
#include "Graph.h"
#include "ThreadPool.h"

/// <summary>
/// Realization of graph with multithreading
/// </summary>
class GraphMT : public Graph
{
private:
    ThreadPool pool; // Thread pool object

public:
    GraphMT(std::vector<Edge>& edges, lng V, size_t num_threads)
        : Graph(edges, V), pool(num_threads) {}

    std::vector<std::vector<lng>> Johnson(lng E, std::vector<std::vector<lng>>& paths) override;
};