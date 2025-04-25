/**
 * @file CalcTree7.cpp
 * @brief Реализация функций для решения задачи CalcTree7
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

/**
 * @brief Функциональный объект для проверки операции
 */
struct IsOperation {
    bool operator()(int val) const {
        return val <= -1 && val >= -6;
    }
};

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

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
                default: break;
            }
        }
    }
    
    return tokens;
}

shared_ptr<TreeNode> buildTree(const vector<int>& tokens) {
    stack<shared_ptr<TreeNode>> st;
    IsOperation isOp;
    
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        int val = *it;
        auto node = make_shared<TreeNode>(val);
        
        if (isOp(val)) {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }
        
        st.push(node);
    }
    
    return st.top();
}

int evaluateSubtree(shared_ptr<TreeNode> node) {
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
}

void transformTree(shared_ptr<TreeNode>& node) {
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
}

void printPrefix(shared_ptr<TreeNode> node) {
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
}
