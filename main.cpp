#include <iostream>
#include <vector>
#include "PerformanceTester.h"

int main() {
    std::vector<int> testSizes = {5000, 10000, 15000, 20000, 30000, 40000, 60000, 100000};
    int iloscTestow = 3;

    std::cout << "Wielkosci testow: ";
    for (int size : testSizes) {
        std::cout << size << " ";
    }

    PerformanceTester tests(testSizes, iloscTestow);
    tests.runAllTests();

    tests.printResults();

    std::cout << "Testy zakonczone pomyslnie" << std::endl;

    return 0;
}