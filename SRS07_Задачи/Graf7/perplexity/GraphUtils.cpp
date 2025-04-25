/**
 * @file GraphUtils.cpp
 * @brief Реализация функций и классов для работы с графом (функциональный стиль)
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
        exit(EXIT_FAILURE);
    }

    file >> n;
    vector<vector<int>> graph(n, vector<int>(n));

    for (auto& row : graph) {
        for (auto& val : row) {
            file >> val;
        }
    }

    return graph;
}

set<int> ReachableCitiesFinder::operator()(const vector<vector<int>>& graph, int start, int L) const {
    int n = static_cast<int>(graph.size());
    set<int> reachable;
    queue<pair<int, int>> q; // {город, уровень}

    q.emplace(start, 0);
    reachable.insert(start);

    while (!q.empty()) {
        auto [city, level] = q.front();
        q.pop();

        if (level >= L) continue;

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[city][neighbor] && !reachable.count(neighbor)) {
                reachable.insert(neighbor);
                q.emplace(neighbor, level + 1);
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

vector<int> toOneBased(vector<int> cities) {
    for (auto& city : cities) {
        city += 1;
    }
    return cities;
}

void printResult(const vector<int>& result) {
    if (result.empty()) {
        cout << -1 << '\n';
        return;
    }
    for (int city : result) {
        cout << city << ' ';
    }
    cout << '\n';
}
