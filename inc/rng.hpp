#pragma once

#include <random>
#include <stdexcept>

class Randomizer {
    public:
        Randomizer() : rng(std::random_device{}()) {}

        int rand_int(int min, int max) {
            std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
            return dist(rng);
        }

        double rand_double(double min, double max) {
            std::uniform_real_distribution<double> dist(min, max);
            return dist(rng);
        }

        template <typename T>
        T rand_choose(const std::vector<double>& weights,
                                    const std::vector<T>& values) {
            if (weights.size() != values.size()) {
                throw std::invalid_argument("weights and values must be the same size");
            } else if (weights.empty()) {
                throw std::invalid_argument("weights and values must be non-empty");
            }
            std::discrete_distribution<> dist(weights.begin(), weights.end());
            return values.at(dist(rng));
        }

    private:
        std::mt19937 rng;
};