#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

// generator liczb losowych

class RandomGenerator {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

public:
    explicit RandomGenerator(int min = 0, int max = INT_MAX) : rng(std::random_device()()), dist(min, max) {}

    int getRandomInt() {
        return dist(rng);
    }

    int getRandomIndex(int size) {
        if (size <= 0) return 0;
        return dist(rng) % size;
    }
};

#endif //RANDOMGENERATOR_H
