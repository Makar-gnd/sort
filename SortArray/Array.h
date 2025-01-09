#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <random>

/**
* @brief Функция быстрой сортировки.
* @param data Вектор, который будет отсортирован.
* @param count счетчик сравнений
* @return Отсортированный вектор.
*/
std::vector<int> QuickSort(std::vector<int>& data, int& count)
{
	if (data.size() < 2) return data;

	int temp = data[0];
	std::vector<int> left;
	std::vector<int> right;
	for (size_t i = 1; i < data.size(); i++)
	{
		count++; 
		if (data[i] < temp)
		{
			left.push_back(data[i]);
		}
		else
		{
			right.push_back(data[i]);
		}
	}

	std::vector<int> temp1 = QuickSort(left, count);
	std::vector<int> temp2 = QuickSort(right, count);
	temp1.push_back(temp);
	temp1.insert(temp1.end(), temp2.begin(), temp2.end());
	return temp1;
}

/**
	* @brief Функция записывающая вектор в строку.
	* @param data Вектор.
	* @return Строка из вектора.
*/
std::string ToString(std::vector<int>& data)
{
	std::ostringstream buffer;
	buffer << "[";
	for (size_t i = 0; i < data.size(); i++)
	{
		buffer << data[i];
		if (i != data.size() - 1)
		{
			buffer << ",";
		}
	}
	buffer << "]";
	return buffer.str();
}

/**
* @brief Заполнение вектора случайными числами от 0 до 9000.
* @param size Требуемый размер вектора.
* @return Вектор случайных чисел.
*/
std::vector<int> random(const int size)
{
	if (size < 1)
	{
		throw std::out_of_range("Неправилный размер массива");
	}
	else
	{
		const int max = 9000;
		const int min = 0;
		//Will be used to obtain a seed for the random number engine
		std::random_device rd;

		//Standard mersenne_twister_engine seeded with rd()
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> uniformIntDistribution(min, max);

		std::vector<int> array;
		for (size_t index = 0; index < size; index++)
		{
			array.push_back(uniformIntDistribution(gen));
		}

		return array;
	}
}

/**
* @brief Сортировка вставками.
* @param data Сортируемый массив.
* @param counter счетчик сдвигов.
* @return Отсортированный массив.
*/
std::vector<int> InsertSort(const std::vector<int>& data, int& counter)
{
	std::vector<int> sortedArr = data; 
	auto n = sortedArr.size();

	for (size_t i = 1; i < n; ++i)
	{
		int key = sortedArr[i];
		int j = i - 1;

		while (j >= 0 && sortedArr[j] > key)
		{
			sortedArr[j + 1] = sortedArr[j];
			--j;
			counter++; 
		}
		sortedArr[j + 1] = key;
	}
	return sortedArr; // Возвращаем отсортированный вектор
}

/**
* @brief Сортировка пузырьком.
* @param data Сортируемый массив.
* @param swap_count счетчик обменов.
* @return Отсортированный массив.
*/
std::vector<int> BubbleSort(const std::vector<int>& data, int& swap_count)
{
    std::vector<int> sortedArr = data; // Создаем копию исходного вектора
    auto n = sortedArr.size();
    bool swapped = true; // Изначально предполагаем, что произошли обмены

    for (size_t i = 0; i < n - 1 && swapped; ++i) { // Цикл продолжается пока swapped = true
        swapped = false; // Сбрасываем флаг в начале каждого прохода
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (sortedArr[j] > sortedArr[j + 1]) {
                std::swap(sortedArr[j], sortedArr[j + 1]);
                swapped = true; // Если произошел обмен, устанавливаем флаг
                swap_count++; 
            }
        }
    }

    return sortedArr; // Возвращаем отсортированный массив
}
