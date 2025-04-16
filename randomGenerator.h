#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>
#include <vector>

// generator liczb losowych
class RandomGenerator {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
    unsigned int current_seed;

    static const std::vector<unsigned int> DEFAULT_SEEDS;

public:
    explicit RandomGenerator(int min = 0, int max = INT_MAX, unsigned int seed = std::random_device()())
        : rng(seed), dist(min, max), current_seed(seed) {}

    void setSeed(unsigned int seed) {
        current_seed = seed;
        rng.seed(seed);
    }

    unsigned int getCurrentSeed() const {
        return current_seed;
    }

    static const std::vector<unsigned int>& getDefaultSeeds() {
        return DEFAULT_SEEDS;
    }

    int getRandomInt() {
        return dist(rng);
    }

    int getRandomIndex(int size) {
        if (size <= 0) return 0;
        return dist(rng) % size;
    }
};


const std::vector<unsigned int> RandomGenerator::DEFAULT_SEEDS = {12345, 67890, 24680};

#endif //RANDOMGENERATOR_H