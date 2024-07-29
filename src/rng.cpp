#include "rng.hpp"

Randomizer::Randomizer() : rng(std::random_device{}()) {}

int Randomizer::rand_int(int min, int max) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

double Randomizer::rand_double(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}