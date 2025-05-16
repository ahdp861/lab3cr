/**
 * @file GraphUtils.h
 * @brief Объявления функций для работы с графом (классический стиль)
 */

#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H

#include <vector>
#include <set>
#include <string>

/**
 * @brief Читает матрицу смежности из файла
 * @param file_name Имя файла
 * @param city_count Количество городов (выходной параметр)
 * @return Матрица смежности
 */
std::vector<std::vector<int>> ReadGraph(const std::string& file_name, int& city_count);

/**
 * @brief Находит города, достижимые из заданного с не более чем L пересадками
 * @param graph Матрица смежности
 * @param start_city Начальный город (0-based индекс)
 * @param max_transfers Максимальное количество пересадок
 * @return Множество достижимых городов (0-based индексы)
 */
std::set<int> FindReachableCities(const std::vector<std::vector<int>>& graph, int start_city, int max_transfers);

/**
 * @brief Находит пересечение двух множеств городов
 * @param first_set Первое множество городов
 * @param second_set Второе множество городов
 * @return Вектор общих городов, отсортированный по возрастанию
 */
std::vector<int> FindCommonCities(const std::set<int>& first_set, const std::set<int>& second_set);

#endif  // GRAPHUTILS_H
