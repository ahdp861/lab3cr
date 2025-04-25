/**
 * @file graf7_functional.cpp
 * @brief Решение задачи Graf7 (функциональный стиль)
 * 
 * Реализация с использованием функциональных возможностей C++ - лямбда-функций,
 * алгоритмов STL и функциональных объектов.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <functional>

using namespace std;

/**
 * @brief Читает матрицу смежности из файла
 * @param filename Имя файла
 * @param n Количество городов (выходной параметр)
 * @return Матрица смежности
 */
auto readGraph = [](const string& filename, int& n) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        exit(1);
    }
    
    file >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    
    for (auto& row : graph) {
        for (auto& val : row) {
            file >> val;
        }
    }
    
    return graph;
};

/**
 * @brief Функциональный объект для поиска достижимых городов
 */
class ReachableCitiesFinder {
public:
    /**
     * @brief Находит города, достижимые из заданного с не более чем L пересадками
     * @param graph Матрица смежности
     * @param start Начальный город (0-based индекс)
     * @param L Максимальное количество пересадок
     * @return Множество достижимых городов (0-based индексы)
     */
    set<int> operator()(const vector<vector<int>>& graph, int start, int L) const {
        int n = graph.size();
        set<int> reachable;
        queue<pair<int, int>> q; // {город, уровень}
        
        q.push({start, 0});
        reachable.insert(start);
        
        while (!q.empty()) {
            auto [city, level] = q.front();
            q.pop();
            
            if (level >= L) continue;
            
            for (int neighbor = 0; neighbor < n; ++neighbor) {
                if (graph[city][neighbor] && !reachable.count(neighbor)) {
                    reachable.insert(neighbor);
                    q.push({neighbor, level + 1});
                }
            }
        }
        
        return reachable;
    }
};

/**
 * @brief Находит пересечение двух множеств городов
 * @param set1 Первое множество городов
 * @param set2 Второе множество городов
 * @return Вектор общих городов, отсортированный по возрастанию
 */
auto findCommonCities = [](const set<int>& set1, const set<int>& set2) {
    vector<int> result;
    set_intersection(set1.begin(), set1.end(),
                    set2.begin(), set2.end(),
                    back_inserter(result));
    return result;
};

/**
 * @brief Преобразует индексы городов из 0-based в 1-based
 * @param cities Вектор городов (0-based)
 * @return Вектор городов (1-based)
 */
auto toOneBased = [](vector<int>& cities) {
    transform(cities.begin(), cities.end(), cities.begin(), [](int city) {
        return city + 1;
    });
    return cities;
};

/**
 * @brief Выводит результат в требуемом формате
 * @param result Вектор с результатами
 */
auto printResult = [](const vector<int>& result) {
    if (result.empty()) {
        cout << -1 << endl;
    } else {
        for (int city : result) {
            cout << city << " ";
        }
        cout << endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " filename" << endl;
        return 1;
    }
    
    int n;
    auto graph = readGraph(argv[1], n);
    
    int K1, K2, L;
    cout << "Введите номера городов K1 и K2 (1-based) и максимальное число пересадок L: ";
    cin >> K1 >> K2 >> L;
    
    // Преобразуем в 0-based индексы
    K1--;
    K2--;
    
    ReachableCitiesFinder finder;
    auto reachableFromK1 = finder(graph, K1, L);
    auto reachableFromK2 = finder(graph, K2, L);
    
    auto commonCities = findCommonCities(reachableFromK1, reachableFromK2);
    auto result = toOneBased(commonCities);
    
    printResult(result);
    
    return 0;
}