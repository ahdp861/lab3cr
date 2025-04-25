/**
 * @file GraphUtils.h
 * @brief Интерфейс функций и классов для работы с графом (функциональный стиль)
 */

#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H

#include <vector>
#include <set>
#include <string>

/**
 * @brief Функциональный объект для поиска достижимых городов
 */
class ReachableCitiesFinder {
public:
    /**
     * @brief Находит города, достижимые из заданного с не более чем L пересадками
     * @param graph Матрица смежности
     * @param start Начальный город (0-based индекс)
     * @param L Максимальное число пересадок
     * @return Множество достижимых городов (0-based индексы)
     */
    std::set<int> operator()(const std::vector<std::vector<int>>& graph, int start, int L) const;
};

/**
 * @brief Читает матрицу смежности из файла
 * @param filename Имя файла
 * @param n Количество городов (выходной параметр)
 * @return Матрица смежности
 */
std::vector<std::vector<int>> readGraph(const std::string& filename, int& n);

/**
 * @brief Находит пересечение двух множеств городов
 * @param set1 Первое множество городов
 * @param set2 Второе множество городов
 * @return Отсортированный вектор общих городов
 */
std::vector<int> findCommonCities(const std::set<int>& set1, const std::set<int>& set2);

/**
 * @brief Преобразует индексы городов из 0-based в 1-based
 * @param cities Вектор городов (0-based)
 * @return Вектор городов (1-based)
 */
std::vector<int> toOneBased(std::vector<int> cities);

/**
 * @brief Выводит результат в требуемом формате
 * @param result Вектор городов
 */
void printResult(const std::vector<int>& result);

#endif // GRAPHUTILS_H
