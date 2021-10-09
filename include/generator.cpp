#include "generator.hpp"

std::random_device device;
std::mt19937 rng(device());

// Integer generator
int generateIntInRange(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

