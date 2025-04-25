/**
 * @file main.cpp
 * @brief Точка входа для решения задачи Graf7 (функциональный стиль)
 */

#include <iostream>
#include "GraphUtils.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " filename\n";
        return EXIT_FAILURE;
    }

    int n = 0;
    auto graph = readGraph(argv[1], n);

    int K1, K2, L;
    std::cout << "Введите номера городов K1 и K2 (1-based) и максимальное число пересадок L: ";
    std::cin >> K1 >> K2 >> L;

    // Переводим в 0-based индексы
    --K1; --K2;

    ReachableCitiesFinder finder;
    auto reachableFromK1 = finder(graph, K1, L);
    auto reachableFromK2 = finder(graph, K2, L);

    auto commonCities = findCommonCities(reachableFromK1, reachableFromK2);
    auto result = toOneBased(commonCities);

    printResult(result);

    return 0;
}
