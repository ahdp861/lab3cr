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
 * @param filename Имя файла
 * @param n Количество городов (выходной параметр)
 * @return Матрица смежности
 */
std::vector<std::vector<int>> readGraph(const std::string& filename, int& n);

/**
 * @brief Находит города, достижимые из заданного с не более чем L пересадками
 * @param graph Матрица смежности
 * @param start Начальный город (0-based индекс)
 * @param L Максимальное количество пересадок
 * @return Множество достижимых городов (0-based индексы)
 */
std::set<int> findReachableCities(const std::vector<std::vector<int>>& graph, int start, int L);

/**
 * @brief Находит пересечение двух множеств городов
 * @param set1 Первое множество городов
 * @param set2 Второе множество городов
 * @return Вектор общих городов, отсортированный по возрастанию
 */
std::vector<int> findCommonCities(const std::set<int>& set1, const std::set<int>& set2);

#endif // GRAPHUTILS_H
