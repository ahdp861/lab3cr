/**
 * @file calctree7_classic.cpp
 * @brief Решение задачи CalcTree7 (классический стиль)
 * 
 * Программа строит дерево выражения в префиксной форме, вычисляет значения поддеревьев,
 * которые являются числами от 0 до 9, и заменяет такие поддеревья их значениями.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <memory>
#include <cctype>

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
 * @brief Создает новый узел дерева
 * @param val Значение узла
 * @return Указатель на созданный узел
 */
shared_ptr<TreeNode> createNode(int val) {
    return make_shared<TreeNode>(val);
}

/**
 * @brief Проверяет, является ли значение кодом операции
 * @param val Проверяемое значение
 * @return true если это операция, иначе false
 */
bool isOperation(int val) {
    return val <= -1 && val >= -6;
}

/**
 * @brief Читает выражение из файла
 * @param filename Имя файла
 * @return Вектор токенов выражения
 */
vector<int> readExpression(const string& filename) {
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
                default: break; // Игнорируем другие символы
            }
        }
    }
    
    return tokens;
}

/**
 * @brief Строит дерево выражения из префиксной формы
 * @param tokens Вектор токенов
 * @return Указатель на корень дерева
 */
shared_ptr<TreeNode> buildTree(const vector<int>& tokens) {
    stack<shared_ptr<TreeNode>> st;
    
    // Обрабатываем токены в обратном порядке для префиксной записи
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        int val = *it;
        auto node = createNode(val);
        
        if (isOperation(val)) {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }
        
        st.push(node);
    }
    
    return st.top();
}

/**
 * @brief Вычисляет значение поддерева
 * @param node Корень поддерева
 * @return Значение поддерева
 */
int evaluateSubtree(shared_ptr<TreeNode> node) {
    if (!isOperation(node->value)) {
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
}

/**
 * @brief Преобразует дерево, заменяя поддеревья с результатами 0-9 на листья
 * @param node Корень дерева
 */
void transformTree(shared_ptr<TreeNode> node) {
    if (!node) return;
    
    transformTree(node->left);
    transformTree(node->right);
    
    if (isOperation(node->value)) {
        int result = evaluateSubtree(node);
        if (result >= 0 && result <= 9) {
            node->value = result;
            node->left = nullptr;
            node->right = nullptr;
        }
    }
}

/**
 * @brief Выводит дерево в префиксной форме
 * @param node Корень дерева
 */
void printPrefix(shared_ptr<TreeNode> node) {
    if (!node) return;
    
    if (isOperation(node->value)) {
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
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " filename" << endl;
        return 1;
    }
    
    vector<int> tokens = readExpression(argv[1]);
    shared_ptr<TreeNode> root = buildTree(tokens);
    
    cout << "Исходное дерево (префиксная форма): ";
    printPrefix(root);
    cout << endl;
    
    transformTree(root);
    
    cout << "Преобразованное дерево (префиксная форма): ";
    printPrefix(root);
    cout << endl;
    
    return 0;
}