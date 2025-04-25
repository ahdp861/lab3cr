/**
 * @file graf7_oop.cpp
 * @brief Решение задачи Graf7 (ООП стиль)
 * 
 * Реализация с использованием классов Graph и CityAnalyzer для работы с графами
 * и анализа городов.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

/**
 * @brief Класс для представления графа городов
 */
class Graph {
private:
    vector<vector<int>> adjacencyMatrix;
    int numCities;
    
public:
    /**
     * @brief Конструктор Graph
     * @param filename Имя файла с матрицей смежности
     */
    Graph(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Не удалось открыть файл: " << filename << endl;
            exit(1);
        }
        
        file >> numCities;
        adjacencyMatrix.resize(numCities, vector<int>(numCities));
        
        for (int i = 0; i < numCities; ++i) {
            for (int j = 0; j < numCities; ++j) {
                file >> adjacencyMatrix[i][j];
            }
        }
    }
    
    /**
     * @brief Возвращает количество городов
     * @return Количество городов
     */
    int getNumCities() const {
        return numCities;
    }
    
    /**
     * @brief Проверяет наличие дороги между городами
     * @param from Город отправления (0-based)
     * @param to Город назначения (0-based)
     * @return true если дорога существует, иначе false
     */
    bool hasRoad(int from, int to) const {
        return adjacencyMatrix[from][to] != 0;
    }
    
    /**
     * @brief Возвращает список соседей города
     * @param city Город (0-based)
     * @return Вектор соседних городов
     */
    vector<int> getNeighbors(int city) const {
        vector<int> neighbors;
        for (int i = 0; i < numCities; ++i) {
            if (hasRoad(city, i)) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }
};

/**
 * @brief Класс для анализа городов и их связей
 */
class CityAnalyzer {
private:
    const Graph& graph;
    
public:
    /**
     * @brief Конструктор CityAnalyzer
     * @param graph Ссылка на объект Graph
     */
    CityAnalyzer(const Graph& g) : graph(g) {}
    
    /**
     * @brief Находит города, достижимые из заданного с не более чем L пересадками
     * @param start Начальный город (0-based)
     * @param L Максимальное количество пересадок
     * @return Множество достижимых городов (0-based)
     */
    set<int> findReachableCities(int start, int L) const {
        set<int> reachable;
        queue<pair<int, int>> q; // {город, уровень}
        
        q.push({start, 0});
        reachable.insert(start);
        
        while (!q.empty()) {
            auto [city, level] = q.front();
            q.pop();
            
            if (level >= L) continue;
            
            for (int neighbor : graph.getNeighbors(city)) {
                if (!reachable.count(neighbor)) {
                    reachable.insert(neighbor);
                    q.push({ne