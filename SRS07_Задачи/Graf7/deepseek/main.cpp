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
    auto graph = ReadGraph(argv[1], n);
    
    int k1, k2, l;
    std::cout << "Введите номера городов K1 и K2 (1-based) и максимальное число пересадок L: ";
    std::cin >> k1 >> k2 >> l;
    
    // Преобразуем в 0-based индексы
    k1--;
    k2--;
    
    auto reachable_from_k1 = FindReachableCities(graph, k1, l);
    auto reachable_from_k2 = FindReachableCities(graph, k2, l);
    
    auto common_cities = FindCommonCities(reachable_from_k1, reachable_from_k2);
    
    // Преобразуем обратно в 1-based индексы
    for (auto& city : common_cities) city++;
    
    if (common_cities.empty()) {
        std::cout << -1 << std::endl;
    } else {
        for (int city : common_cities) {
            std::cout << city << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
