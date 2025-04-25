/**
 * @file main.cpp
 * @brief Точка входа в программу решения задачи Graf7 (классический стиль)
 */

#include <iostream>
#include "GraphUtils.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " filename" << std::endl;
        return 1;
    }
    
    int n;
    auto graph = readGraph(argv[1], n);
    
    int K1, K2, L;
    std::cout << "Введите номера городов K1 и K2 (1-based) и максимальное число пересадок L: ";
    std::cin >> K1 >> K2 >> L;
    
    // Преобразуем в 0-based индексы
    K1--;
    K2--;
    
    auto reachableFromK1 = findReachableCities(graph, K1, L);
    auto reachableFromK2 = findReachableCities(graph, K2, L);
    
    auto commonCities = findCommonCities(reachableFromK1, reachableFromK2);
    
    // Преобразуем обратно в 1-based индексы
    for (auto& city : commonCities) city++;
    
    if (commonCities.empty()) {
        std::cout << -1 << std::endl;
    } else {
        for (int city : commonCities) {
            std::cout << city << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
