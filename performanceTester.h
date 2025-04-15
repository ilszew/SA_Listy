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
protected:
    Timer timer;
    RandomGenerator rng;
    std::vector<int> testSizes;
    int numRepeats;
    static constexpr int numDataStructures = 3;

    std::vector<std::vector<double>> addFirstResults;
    std::vector<std::vector<double>> addLastResults;
    std::vector<std::vector<double>> addRandomResults;
    std::vector<std::vector<double>> removeFirstResults;
    std::vector<std::vector<double>> removeLastResults;
    std::vector<std::vector<double>> removeRandomResults;
    std::vector<std::vector<double>> searchResults;

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
        addFirstResults.resize(numDataStructures, std::vector<double>(testSizes.size(), 0.0));
        addLastResults.resize(numDataStructures, std::vector<double>(testSizes.size(), 0.0));
        addRandomResults.resize(numDataStructures, std::vector<double>(testSizes.size(), 0.0));
        removeFirstResults.resize(numDataStructures, std::vector<double>(testSizes.size(), 0.0));
        removeLastResults.resize(numDataStructures, std::vector<double>(testSizes.size(), 0.0));
        removeRandomResults.resize(numDataStructures, std::vector<double>(testSizes.size(), 0.0));
        searchResults.resize(numDataStructures, std::vector<double>(testSizes.size(), 0.0));
    }

    void runAllTests() {
        for (size_t i = 0; i < testSizes.size(); i++) {
            int size = testSizes[i];
            std::cout << "Testy dla rozmiaru: " << size << std::endl;

            for (int repeat = 0; repeat < numRepeats; repeat++) {
                std::cout << "  Powtorzenie " << repeat + 1 << "/" << numRepeats << "..." << std::endl;

                std::vector<int> randomData = generateRandomData(size);

                testArrayList(randomData, i);

                testSinglyLinkedList(randomData, i);

                testDoublyLinkedList(randomData, i);
            }

            calculateAverages(i);
        }

    }

    void testArrayList(const std::vector<int>& data, size_t sizeIndex) {
        ArrayList<int> list;

        timer.startTimer();
        for (const auto& value : data) {
            list.DodajP(value);
        }
        double addFirstTime = timer.stopTimer();
        addFirstResults[0][sizeIndex] += addFirstTime;

        list = ArrayList<int>();

        timer.startTimer();
        for (const auto& value : data) {
            list.DodajK(value);
        }
        double addLastTime = timer.stopTimer();
        addLastResults[0][sizeIndex] += addLastTime;

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
        addRandomResults[0][sizeIndex] += addRandomTime;

        std::vector<int> searchValues = generateRandomData(100);
        timer.startTimer();
        for (const auto& value : searchValues) {
            list.Szukaj(value);
        }
        double searchTime = timer.stopTimer();
        searchResults[0][sizeIndex] += searchTime;

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.wielkosc() > 0; i++) {
            try {
                list.UsunP();
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeFirstTime = timer.stopTimer();
        removeFirstResults[0][sizeIndex] += removeFirstTime;

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
        removeLastResults[0][sizeIndex] += removeLastTime;

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
        removeRandomResults[0][sizeIndex] += removeRandomTime;
    }

    void testSinglyLinkedList(const std::vector<int>& data, size_t sizeIndex) {
        SinglyLinkedList<int> list;

        timer.startTimer();
        for (const auto& value : data) {
            list.addFirst(value);
        }
        double addFirstTime = timer.stopTimer();
        addFirstResults[1][sizeIndex] += addFirstTime;

        list = SinglyLinkedList<int>(); // Reset list

        timer.startTimer();
        for (const auto& value : data) {
            list.addLast(value);
        }
        double addLastTime = timer.stopTimer();
        addLastResults[1][sizeIndex] += addLastTime;

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
        addRandomResults[1][sizeIndex] += addRandomTime;

        std::vector<int> searchValues = generateRandomData(100);
        timer.startTimer();
        for (const auto& value : searchValues) {
            list.search(value);
        }
        double searchTime = timer.stopTimer();
        searchResults[1][sizeIndex] += searchTime;

        timer.startTimer();
        for (size_t i = 0; i < data.size() && list.getSize() > 0; i++) {
            try {
                list.removeFirst();
            } catch (const std::out_of_range&) {
                break;
            }
        }
        double removeFirstTime = timer.stopTimer();
        removeFirstResults[1][sizeIndex] += removeFirstTime;

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
        removeLastResults[1][sizeIndex] += removeLastTime;

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
        removeRandomResults[1][sizeIndex] += removeRandomTime;
    }

    void testDoublyLinkedList(const std::vector<int>& data, size_t sizeIndex) {
        DoublyLinkedList<int> list;

        timer.startTimer();
        for (const auto& value : data) {
            list.pushFront(value);
        }
        double addFirstTime = timer.stopTimer();
        addFirstResults[2][sizeIndex] += addFirstTime;

        list = DoublyLinkedList<int>();

        timer.startTimer();
        for (const auto& value : data) {
            list.pushBack(value);
        }
        double addLastTime = timer.stopTimer();
        addLastResults[2][sizeIndex] += addLastTime;

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
                // Handle exception if needed
            }
        }
        double addRandomTime = timer.stopTimer();
        addRandomResults[2][sizeIndex] += addRandomTime;

        std::vector<int> searchValues = generateRandomData(100);
        timer.startTimer();
        for (const auto& value : searchValues) {
            list.search(value);
        }
        double searchTime = timer.stopTimer();
        searchResults[2][sizeIndex] += searchTime;

        timer.startTimer();
        for (size_t i = 0; i < data.size() && !list.isEmpty(); i++) {
            list.popFront();
        }
        double removeFirstTime = timer.stopTimer();
        removeFirstResults[2][sizeIndex] += removeFirstTime;

        list = DoublyLinkedList<int>();
        for (const auto& value : data) {
            list.pushBack(value);
        }

        timer.startTimer();
        for (size_t i = 0; i < data.size() && !list.isEmpty(); i++) {
            list.popBack();
        }
        double removeLastTime = timer.stopTimer();
        removeLastResults[2][sizeIndex] += removeLastTime;

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
        removeRandomResults[2][sizeIndex] += removeRandomTime;
    }

    void calculateAverages(size_t sizeIndex) {
        for (size_t structIndex = 0; structIndex < numDataStructures; structIndex++) {
            addFirstResults[structIndex][sizeIndex] /= numRepeats;
            addLastResults[structIndex][sizeIndex] /= numRepeats;
            addRandomResults[structIndex][sizeIndex] /= numRepeats;
            removeFirstResults[structIndex][sizeIndex] /= numRepeats;
            removeLastResults[structIndex][sizeIndex] /= numRepeats;
            removeRandomResults[structIndex][sizeIndex] /= numRepeats;
            searchResults[structIndex][sizeIndex] /= numRepeats;
        }
    }

    void printResults() const {
        std::cout << "\n===== WYNIKI WYDAJNOSCI =====\n" << std::endl;

        printOperationResults("Dodawanie na poczatku (ms)", addFirstResults);
        printOperationResults("Dodawanie na koncu (ms)", addLastResults);
        printOperationResults("Dodawanie w losowych miejcach (ms)", addRandomResults);
        printOperationResults("Usuwanie z poczatku (ms)", removeFirstResults);
        printOperationResults("Usuwanie z konca (ms)", removeLastResults);
        printOperationResults("Usuwanie z losowych miejsc (ms)", removeRandomResults);
        printOperationResults("Szukanie (ms)", searchResults);
    }

    void printOperationResults(const std::string& operationName, const std::vector<std::vector<double>>& results) const {
        std::cout << operationName << ":" << std::endl;
        std::cout << std::setw(10) << "Wielkosc" << std::setw(15) << "ArrayList" << std::setw(20) << "SinglyLinkedList" << std::setw(20) << "DoublyLinkedList" << std::endl;

        for (size_t i = 0; i < testSizes.size(); i++) {
            std::cout << std::setw(10) << testSizes[i];
            for (size_t j = 0; j < results.size(); j++) {
                std::cout << std::setw(j == 0 ? 15 : 20) << std::fixed << std::setprecision(4) << results[j][i];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif //PERFORMANCETESTER_H