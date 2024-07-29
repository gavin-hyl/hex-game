#pragma once

#include <random>
#include <stdexcept>

class Randomizer {
    public:
        Randomizer();

        int rand_int(int min, int max);

        double rand_double(double min, double max);

        template <class T>
        T rand_choose(const std::vector<T>& values, 
                      const std::vector<double>& weights);

        template <class T>
        std::vector<T> rand_choose_noreplace(std::vector<T> values, int n);

    private:
        std::mt19937 rng;
};

template <typename T>
T Randomizer::rand_choose(const std::vector<T>& values, 
                          const std::vector<double>& weights) {
    if (weights.size() != values.size()) {
        throw std::invalid_argument("weights and values must be the same size");
    } else if (weights.empty()) {
        throw std::invalid_argument("weights and values must be non-empty");
    }
    std::discrete_distribution<> dist(weights.begin(), weights.end());
    return values.at(dist(rng));
}

template <typename T>
std::vector<T> Randomizer::rand_choose_noreplace(std::vector<T> values, int n) {
    if (values.empty()) {
        throw std::invalid_argument("values must be non-empty");
    }
    std::shuffle(values.begin(), values.end(), rng);
    return std::vector<T>(values.begin(), values.begin() + n);
}