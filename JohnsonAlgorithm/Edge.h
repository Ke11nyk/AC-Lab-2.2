#pragma once

#define lng long long

/// <summary>
/// Struct to specify an edge as from to weight
/// </summary>
struct Edge {
    lng from;
    lng to;
    lng weight;

    /// <summary>
    /// Constructor of the edge
    /// </summary>
    /// <param name="f">Start vertex</param>
    /// <param name="t">Final vertex</param>
    /// <param name="w">Weight of edge</param>
    Edge(lng f, lng t, lng w) : from(f), to(t), weight(w) {}
};