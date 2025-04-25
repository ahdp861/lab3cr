/**
 * @file ExpressionTree.cpp
 * @brief Реализация классов для решения задачи CalcTree7 (ООП стиль)
 */

#include "ExpressionTree.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <cctype>

using namespace std;

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

bool TreeNode::isOperation() const {
    return value <= -1 && value >= -6;
}

shared_ptr<TreeNode> ExpressionTree::createNode(int val) const {
    return make_shared<TreeNode>(val);
}

int ExpressionTree::evaluateSubtree(shared_ptr<TreeNode> node) const {
    if (!node->isOperation()) {
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

vector<int> ExpressionTree::readExpression(const string& filename) const {
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

shared_ptr<TreeNode> ExpressionTree::buildTree(const vector<int>& tokens) {
    stack<shared_ptr<TreeNode>> st;

    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        int val = *it;
        auto node = createNode(val);

        if (node->isOperation()) {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }

        st.push(node);
    }

    return st.top();
}

void ExpressionTree::transformTree() {
    transformTree(root);
}

void ExpressionTree::transformTree(shared_ptr<TreeNode> node) {
    if (!node) return;

    transformTree(node->left);
    transformTree(node->right);

    if (node->isOperation()) {
        int result = evaluateSubtree(node);
        if (result >= 0 && result <= 9) {
            node->value = result;
            node->left = nullptr;
            node->right = nullptr;
        }
    }
}

void ExpressionTree::printPrefix() const {
    printPrefix(root);
    cout << endl;
}

void ExpressionTree::printPrefix(shared_ptr<TreeNode> node) const {
    if (!node) return;

    if (node->isOperation()) {
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

ExpressionTree::ExpressionTree(const string& filename) {
    root = buildTree(readExpression(filename));
}
