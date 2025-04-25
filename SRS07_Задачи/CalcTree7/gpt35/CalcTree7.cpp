/**
 * @file CalcTree7.cpp
 * @brief Реализация функций для решения задачи CalcTree7 (классический стиль)
 */

#include "CalcTree7.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <cctype>

using namespace std;

// Коды операций
const int ADD = -1;
const int SUB = -2;
const int MUL = -3;
const int DIV = -4;
const int MOD = -5;
const int POW = -6;

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

shared_ptr<TreeNode> createNode(int val) {
    return make_shared<TreeNode>(val);
}

bool isOperation(int val) {
    return val <= -1 && val >= -6;
}

vector<int> readExpression(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        exit(1);
    }

    vector<int> tokens;
    char c;
    while (file >> c) {
        if (isdigit(static_cast<unsigned char>(c))) {
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
