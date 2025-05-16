/**
 * @file GraphUtils.cpp
 * @brief Реализация функций для работы с графом (классический стиль)
 */

#include "GraphUtils.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> ReadGraph(const string& file_name, int& n) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Не удалось открыть файл: " << file_name << endl;
        exit(1);
    }
    
    file >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> graph[i][j];
        }
    }
    
    return graph;
}

set<int> FindReachableCities(const vector<vector<int>>& graph, int start_city, int max_level) {
    int n = static_cast<int>(graph.size());
    set<int> reachable_cities;
    queue<pair<int, int>> q; // {город, уровень}
    
    q.push({start_city, 0});
    reachable_cities.insert(start_city);
    
    while (!q.empty()) {
        auto [city, level] = q.front();
        q.pop();
        
        if (level >= max_level) continue;
        
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[city][neighbor] && !reachable_cities.count(neighbor)) {
                reachable_cities.insert(neighbor);
                q.push({neighbor, level + 1});
            }
        }
    }
    
    return reachable_cities;
}

vector<int> FindCommonCities(const set<int>& set_1, const set<int>& set_2) {
    vector<int> result;
    set_intersection(set_1.begin(), set_1.end(),
                     set_2.begin(), set_2.end(),
                     back_inserter(result));
    return result;
}
