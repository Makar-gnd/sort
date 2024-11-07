#include "Array.h"
void TestSortingAlgorithms(int size)
{
    std::vector<int> data = random(size);

    // Для быстрой сортировки
    std::vector<int> quickSortData = data;
    int quickSortComparisons = 0;
    quickSortData = QuickSort(quickSortData, quickSortComparisons);
    std::cout << "QuickSort: " << ToString(quickSortData) << std::endl;
    std::cout << "Comparisons in QuickSort: " << quickSortComparisons << std::endl;

    // Для сортировки вставками
    std::vector<int> insertSortData = data;
    int insertSortShifts = 0;
    insertSortData = InsertSort(insertSortData, insertSortShifts);
    std::cout << "InsertSort: " << ToString(insertSortData) << std::endl;
    std::cout << "Shifts in InsertSort: " << insertSortShifts << std::endl;

    // Для сортировки пузырьком
    std::vector<int> bubbleSortData = data;
    int bubbleSortSwaps = 0;
    bubbleSortData = BubbleSort(bubbleSortData, bubbleSortSwaps);
    std::cout << "BubbleSort: " << ToString(bubbleSortData) << std::endl;
    std::cout << "Swaps in BubbleSort: " << bubbleSortSwaps << std::endl;
}

int main() {
    int size = 1000; // Размер вектора для сортировки
    TestSortingAlgorithms(size);
    return 0;
}