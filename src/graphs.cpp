#include "graphs.hpp"

template <typename T>
std::vector<T> connected(std::vector<T> nodes, T start, std::function<std::vector<T>(T)> adjacent) {
    std::set<T> frontier = {start};
    std::set<T> visited;
    while (!frontier.empty()) {
        T current = *frontier.begin();
        frontier.erase(frontier.begin());
        visited.insert(current);
        for (T neighbor : adjacent(current)) {
            if (nodes.count(neighbor) && !visited.count(neighbor)) {
                frontier.insert(neighbor);
            }
        }
    }
    return visited;
}