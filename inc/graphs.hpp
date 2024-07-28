#pragma once

#include <vector>
#include <set>
#include <functional>

// simplified version of dijkstra's algorithm, the frontier is a set of nodes
// that are connected to the start node.
template <typename T>
std::vector<T> connected(std::vector<T> nodes, T start, std::function<std::vector<T>(T)> adjacent);