#ifndef PERFORMANCETESTER_H
#define PERFORMANCETESTER_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "Timer.h"
#include "RandomGenerator.h"
#include "arrayList.h"
#include "singlyLinkedList.h"
#include "doublyLinkedList.h"

// klasa testowa
class PerformanceTester {
private:
    Timer timer;
    RandomGenerator rng;
    std::vector<int> testSizes;
    int numRepeats;
    static constexpr int numDataStructures = 3;
    static constexpr int numSeeds = 3;

    std::vector<std::vector<std::vector<double>>> addFirstResults;
    std::vector<std::vector<std::vector<double>>> addLastResults;
    std::vector<std::vector<std::vector<double>>> addRandomResults;
    std::vector<std::vector<std::vector<double>>> removeFirstResults;
    std::vector<std::vector<std::vector<double>>> removeLastResults;
    std::vector<std::vector<std::vector<double>>> removeRandomResults;
    std::vector<std::vector<std::vector<double>>> searchResults;

    std::vector<int> generateRandomData(int size) {
        std::vector<int> data;
        data.reserve(static_cast<size_t>(size));
        for (int i = 0; i < size; i++) {
            data.push_back(rng.getRandomInt());
        }
        return data;
    }

public:
    PerformanceTester(const std::vector<int>& sizes, int repeats)
        : testSizes(sizes), numRepeats(repeats) {
        addFirstResults.resize(numDataStructures, std::vector<std::vector<double>>(testSizes.size(), std::vector<double>(numSeeds, 0.0)));
        addLastResults.resize(numDataStructures, std::vector<std::vector<double>>(testSizes.size(), std::vector<double>(numSeeds, 0.0)));
        addRandomResults.resize(numDataStructures, std::vector<std::vector<double>>(testSizes.size(), std::vector<double>(numSeeds, 0.0)));
        removeFirstResults.resize(numDataStructures, std::vector<std::vector<double>>(testSizes.size(), std::vector<double>(numSeeds, 0.0)));
        removeLastResults.resize(numDataStructures, std::vector<std::vector<double>>(testSizes.size(), std::vector<double>(numSeeds, 0.0)));
        removeRandomResults.resize(numDataStructures, std::vector<std::vector<double>>(testSizes.size(), std::vector<double>(numSeeds, 0.0)));
        searchResults.resize(numDataStructures, std::vector<std::vector<double>>(testSizes.size(), std::vector<double>(numSeeds, 0.0)));
    }

    void runAllTests() {
        const std::vector<unsigned int>& seeds = RandomGenerator::getDefaultSeeds();

        for (size_t seedIdx = 0; seedIdx < numSeeds; seedIdx++) {
            unsigned int currentSeed = seeds[seedIdx];
            std::cout << "\n========= Testy dla seed: " << currentSeed << " =========\n" << std::endl;
            rng.setSeed(currentSeed);

            for (size_t i = 0; i < testSizes.size(); i++) {
                int size = testSizes[i];
                std::cout << "Testy dla rozmiaru: " << size << std::endl;

                for (int repeat = 0; repeat < numRepeats; repeat++) {
                    std::cout << "  Powtorzenie " << repeat + 1 << "/" << numRepeats << "..." << std::endl;

                    std::vector<int> randomData = generateRandomData(size);

                    testArrayList(randomData, i, seedIdx);

                    testSinglyLinkedList(randomData, i, seedIdx);

                    testDoublyLinkedList(randomData, i, seedIdx);
                }

                calculateAverages(i, seedIdx);
            }
        }
    }

    void testArrayList(const std::vector<int>& data, size_t sizeIndex, size_t seedIndex) {
        ArrayList<int> list;

        timer.startTimer();
        for (const auto& value : data) {
            list.DodajP(value);
        }
        double addFirstTime = timer.stopTimer();
        addFirstResults[0][sizeIndex][seedIndex] += addFirstTime;

        list = ArrayList<int>();

        timer.startTimer();
        for (const auto& value : data) {
            list.DodajK(value);
        }
        double addLastTime = timer.stopTimer();
        addLastResults[0][sizeIndex][seedIndex] += addLastTime;

        ArrayList<int> randomList;
        for (const auto& value : data) {
            randomList.DodajK(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size(); i++) {
            int randomIndex = rng.getRandomIndex(static_cast<int>(i) + 1);
            randomList.DodajLos(randomIndex, data[i]);
        }
        double addRandomTime = timer.stopTimer();
        addRandomResults[0][sizeIndex][seedIndex] += addRandomTime;

        std::vector<int> searchValues = generateRandomData(100);
        timer.startTimer();
        for (const auto& value : searchValues) {
            list.Szukaj(value);
        }
        double searchTime = timer.stopTimer();
        searchResults[0][sizeIndex][seedIndex] += searchTime;

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.wielkosc() > 0; i++) {
            try {
                list.UsunP();
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeFirstTime = timer.stopTimer();
        removeFirstResults[0][sizeIndex][seedIndex] += removeFirstTime;

        list = ArrayList<int>();
        for (const auto& value : data) {
            list.DodajK(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.wielkosc() > 0; i++) {
            try {
                list.UsunK();
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeLastTime = timer.stopTimer();
        removeLastResults[0][sizeIndex][seedIndex] += removeLastTime;

        list = ArrayList<int>();
        for (const auto& value : data) {
            list.DodajK(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.wielkosc() > 0; i++) {
            try {
                int randomIndex = rng.getRandomIndex(list.wielkosc());
                list.UsunLos(randomIndex);
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeRandomTime = timer.stopTimer();
        removeRandomResults[0][sizeIndex][seedIndex] += removeRandomTime;
    }

    void testSinglyLinkedList(const std::vector<int>& data, size_t sizeIndex, size_t seedIndex) {
        SinglyLinkedList<int> list;

        timer.startTimer();
        for (const auto& value : data) {
            list.addFirst(value);
        }
        double addFirstTime = timer.stopTimer();
        addFirstResults[1][sizeIndex][seedIndex] += addFirstTime;

        list = SinglyLinkedList<int>(); // Reset list

        timer.startTimer();
        for (const auto& value : data) {
            list.addLast(value);
        }
        double addLastTime = timer.stopTimer();
        addLastResults[1][sizeIndex][seedIndex] += addLastTime;

        SinglyLinkedList<int> randomList;
        for (const auto& value : data) {
            randomList.addLast(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size(); i++) {
            int randomIndex = rng.getRandomIndex(static_cast<int>(i) + 1);
            randomList.addAt(randomIndex, data[i]);
        }
        double addRandomTime = timer.stopTimer();
        addRandomResults[1][sizeIndex][seedIndex] += addRandomTime;

        std::vector<int> searchValues = generateRandomData(100);
        timer.startTimer();
        for (const auto& value : searchValues) {
            list.search(value);
        }
        double searchTime = timer.stopTimer();
        searchResults[1][sizeIndex][seedIndex] += searchTime;

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.getSize() > 0; i++) {
            try {
                list.removeFirst();
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeFirstTime = timer.stopTimer();
        removeFirstResults[1][sizeIndex][seedIndex] += removeFirstTime;

        list = SinglyLinkedList<int>();
        for (const auto& value : data) {
            list.addLast(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.getSize() > 0; i++) {
            try {
                list.removeLast();
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeLastTime = timer.stopTimer();
        removeLastResults[1][sizeIndex][seedIndex] += removeLastTime;

        list = SinglyLinkedList<int>();
        for (const auto& value : data) {
            list.addLast(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.getSize() > 0; i++) {
            try {
                int randomIndex = rng.getRandomIndex(list.getSize());
                list.removeAt(randomIndex);
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeRandomTime = timer.stopTimer();
        removeRandomResults[1][sizeIndex][seedIndex] += removeRandomTime;
    }

    void testDoublyLinkedList(const std::vector<int>& data, size_t sizeIndex, size_t seedIndex) {
        DoublyLinkedList<int> list;

        timer.startTimer();
        for (const auto& value : data) {
            list.pushFront(value);
        }
        double addFirstTime = timer.stopTimer();
        addFirstResults[2][sizeIndex][seedIndex] += addFirstTime;

        list = DoublyLinkedList<int>();

        timer.startTimer();
        for (const auto& value : data) {
            list.pushBack(value);
        }
        double addLastTime = timer.stopTimer();
        addLastResults[2][sizeIndex][seedIndex] += addLastTime;

        DoublyLinkedList<int> randomList;
        for (const auto& value : data) {
            randomList.pushBack(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size(); i++) {
            int randomIndex = rng.getRandomIndex(static_cast<int>(i) + 1);
            try {
                randomList.insertAt(randomIndex, data[i]);
            } catch (const std::out_of_range&) {
            }
        }
        double addRandomTime = timer.stopTimer();
        addRandomResults[2][sizeIndex][seedIndex] += addRandomTime;

        std::vector<int> searchValues = generateRandomData(100);
        timer.startTimer();
        for (const auto& value : searchValues) {
            list.search(value);
        }
        double searchTime = timer.stopTimer();
        searchResults[2][sizeIndex][seedIndex] += searchTime;

        timer.startTimer();
        for (size_t i = 0; i < data.size() && !list.isEmpty(); i++) {
            list.popFront();
        }
        double removeFirstTime = timer.stopTimer();
        removeFirstResults[2][sizeIndex][seedIndex] += removeFirstTime;

        list = DoublyLinkedList<int>();
        for (const auto& value : data) {
            list.pushBack(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size() && !list.isEmpty(); i++) {
            list.popBack();
        }
        double removeLastTime = timer.stopTimer();
        removeLastResults[2][sizeIndex][seedIndex] += removeLastTime;

        list = DoublyLinkedList<int>();
        for (const auto& value : data) {
            list.pushBack(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size() && !list.isEmpty(); i++) {
            try {
                int randomIndex = rng.getRandomIndex(list.getSize());
                list.removeAt(randomIndex);
            } catch (const std::out_of_range&) {
            }
        }
        double removeRandomTime = timer.stopTimer();
        removeRandomResults[2][sizeIndex][seedIndex] += removeRandomTime;
    }

    void calculateAverages(size_t sizeIndex, size_t seedIndex) {
        for (size_t structIndex = 0; structIndex < numDataStructures; structIndex++) {
            addFirstResults[structIndex][sizeIndex][seedIndex] /= numRepeats;
            addLastResults[structIndex][sizeIndex][seedIndex] /= numRepeats;
            addRandomResults[structIndex][sizeIndex][seedIndex] /= numRepeats;
            removeFirstResults[structIndex][sizeIndex][seedIndex] /= numRepeats;
            removeLastResults[structIndex][sizeIndex][seedIndex] /= numRepeats;
            removeRandomResults[structIndex][sizeIndex][seedIndex] /= numRepeats;
            searchResults[structIndex][sizeIndex][seedIndex] /= numRepeats;
        }
    }

    [[nodiscard]] static double calculateOverallAverage(const std::vector<std::vector<std::vector<double>>>& results,
                                   size_t structIndex, size_t sizeIndex) {
        double sum = 0.0;
        for (size_t seedIndex = 0; seedIndex < numSeeds; seedIndex++) {
            sum += results[structIndex][sizeIndex][seedIndex];
        }
        return sum / numSeeds;
    }

    void printResults() const {
        std::cout << "\n===== WYNIKI WYDAJNOSCI (średnia z " << numSeeds << " seedów) =====\n" << std::endl;

        printOperationResults("Dodawanie na poczatku (ms)", addFirstResults);
        printOperationResults("Dodawanie na koncu (ms)", addLastResults);
        printOperationResults("Dodawanie w losowych miejcach (ms)", addRandomResults);
        printOperationResults("Usuwanie z poczatku (ms)", removeFirstResults);
        printOperationResults("Usuwanie z konca (ms)", removeLastResults);
        printOperationResults("Usuwanie z losowych miejsc (ms)", removeRandomResults);
        printOperationResults("Szukanie (ms)", searchResults);

        printDetailedResults();
    }

    void printOperationResults(const std::string& operationName,
                              const std::vector<std::vector<std::vector<double>>>& results) const {
        std::cout << operationName << ":" << std::endl;
        std::cout << std::setw(10) << "Wielkosc" << std::setw(15) << "ArrayList"
                  << std::setw(20) << "SinglyLinkedList" << std::setw(20) << "DoublyLinkedList" << std::endl;

        for (size_t i = 0; i < testSizes.size(); i++) {
            std::cout << std::setw(10) << testSizes[i];
            for (size_t j = 0; j < numDataStructures; j++) {
                std::cout << std::setw(j == 0 ? 15 : 20) << std::fixed << std::setprecision(4)
                          << calculateOverallAverage(results, j, i);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void printDetailedResults() const {
        const std::vector<unsigned int>& seeds = RandomGenerator::getDefaultSeeds();
        const std::vector<std::string> dataStructures = {"ArrayList", "SinglyLinkedList", "DoublyLinkedList"};
        const std::vector<std::string> operations = {
            "Dodawanie na poczatku (ms)",
            "Dodawanie na koncu (ms)",
            "Dodawanie w losowych miejcach (ms)",
            "Usuwanie z poczatku (ms)",
            "Usuwanie z konca (ms)",
            "Usuwanie z losowych miejsc (ms)",
            "Szukanie (ms)"
        };

        const std::vector<std::vector<std::vector<std::vector<double>>>> allResults = {
            addFirstResults, addLastResults, addRandomResults,
            removeFirstResults, removeLastResults, removeRandomResults,
            searchResults
        };
    }
};

#endif //PERFORMANCETESTER_H