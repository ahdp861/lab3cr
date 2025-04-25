/**
 * @file calctree7_functional.cpp
 * @brief Решение задачи CalcTree7 (функциональный стиль)
 * 
 * Реализация с использованием функциональных возможностей C++ (лямбда-функции,
 * алгоритмы, функциональные объекты).
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <memory>
#include <cctype>
#include <functional>
#include <algorithm>

using namespace std;

// Коды операций
const int ADD = -1;
const int SUB = -2;
const int MUL = -3;
const int DIV = -4;
const int MOD = -5;
const int POW = -6;

/**
 * @brief Узел дерева выражения
 */
struct TreeNode {
    int value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief Функциональный объект для проверки операции
 */
struct IsOperation {
    bool operator()(int val) const {
        return val <= -1 && val >= -6;
    }
};

/**
 * @brief Читает выражение из файла
 * @param filename Имя файла
 * @return Вектор токенов выражения
 */
auto readExpression = [](const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        exit(1);
    }
    
    vector<int> tokens;
    char c;
    while (file >> c) {
        if (isdigit(c)) {
            tokens.push_back(c - '0');
        } else {
            switch (c) {
                case '+': tokens.push_back(ADD); break;
                case '-': tokens.push_back(SUB); break;
                case '*': tokens.push_back(MUL); break;
                case '/': tokens.push_back(DIV); break;
                case '%': tokens.push_back(MOD); break;
                case '^': tokens.push_back(POW); break;
                default: break;
            }
        }
    }
    
    return tokens;
};

/**
 * @brief Строит дерево выражения из префиксной формы
 * @param tokens Вектор токенов
 * @return Указатель на корень дерева
 */
auto buildTree = [](const vector<int>& tokens) {
    stack<shared_ptr<TreeNode>> st;
    IsOperation isOp;
    
    for_each(tokens.rbegin(), tokens.rend(), [&](int val) {
        auto node = make_shared<TreeNode>(val);
        
        if (isOp(val)) {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }
        
        st.push(node);
    });
    
    return st.top();
};

/**
 * @brief Вычисляет значение поддерева
 * @param node Корень поддерева
 * @return Значение поддерева
 */
function<int(shared_ptr<TreeNode>)> evaluateSubtree = [](shared_ptr<TreeNode> node) {
    IsOperation isOp;
    
    if (!isOp(node->value)) {
        return node->value;
    }
    
    int left = evaluateSubtree(node->left);
    int right = evaluateSubtree(node->right);
    
    switch (node->value) {
        case ADD: return left + right;
        case SUB: return left - right;
        case MUL: return left * right;
        case DIV: return left / right;
        case MOD: return left % right;
        case POW: {
            int result = 1;
            for (int i = 0; i < right; ++i) result *= left;
            return result;
        }
        default: return 0;
    }
};

/**
 * @brief Преобразует дерево, заменяя поддеревья с результатами 0-9 на листья
 * @param node Корень дерева
 */
function<void(shared_ptr<TreeNode>&)> transformTree = [](shared_ptr<TreeNode>& node) {
    if (!node) return;
    
    IsOperation isOp;
    
    transformTree(node->left);
    transformTree(node->right);
    
    if (isOp(node->value)) {
        int result = evaluateSubtree(node);
        if (result >= 0 && result <= 9) {
            node->value = result;
            node->left = nullptr;
            node->right = nullptr;
        }
    }
};

/**
 * @brief Выводит дерево в префиксной форме
 * @param node Корень дерева
 */
function<void(shared_ptr<TreeNode>)> printPrefix = [](shared_ptr<TreeNode> node) {
    if (!node) return;
    
    IsOperation isOp;
    
    if (isOp(node->value)) {
        switch (node->value) {
            case ADD: cout << "+ "; break;
            case SUB: cout << "- "; break;
            case MUL: cout << "* "; break;
            case DIV: cout << "/ "; break;
            case MOD: cout << "% "; break;
            case POW: cout << "^ "; break;
        }
    } else {
        cout << node->value << " ";
    }
    
    printPrefix(node->left);
    printPrefix(node->right);
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " filename" << endl;
        return 1;
    }
    
    auto tokens = readExpression(argv[1]);
    auto root = buildTree(tokens);
    
    cout << "Исходное дерево (префиксная форма): ";
    printPrefix(root);
    cout << endl;
    
    transformTree(root);
    
    cout << "Преобразованное дерево (префиксная форма): ";
    printPrefix(root);
    cout << endl;
    
    return 0;
}