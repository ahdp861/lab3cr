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

vector<vector<int>> readGraph(const string& filename, int& n) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл: " << filename << endl;
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

set<int> findReachableCities(const vector<vector<int>>& graph, int start, int L) {
    int n = static_cast<int>(graph.size());
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

vector<int> findCommonCities(const set<int>& set1, const set<int>& set2) {
    vector<int> result;
    set_intersection(set1.begin(), set1.end(),
                     set2.begin(), set2.end(),
                     back_inserter(result));
    return result;
}
