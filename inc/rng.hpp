#pragma once

#include <random>
#include <stdexcept>
#include <ctime>


template <typename T>
T random_distribution_choose(const std::vector<double>& weights,
                             const std::vector<T>& values) {
    if (weights.size() != values.size()) {
        throw std::invalid_argument("weights and values must be the same size");
    } else if (weights.empty()) {
        throw std::invalid_argument("weights and values must be non-empty");
    }

    double cdf = 0;
    double rand = (double)random() / RAND_MAX;
    for (unsigned int i = 0; i < weights.size(); i++) {
        cdf += weights.at(i);
        if (rand < cdf) {
            return values.at(i);
        }
    }
    throw std::runtime_error("random_distribution_choose failed");
}