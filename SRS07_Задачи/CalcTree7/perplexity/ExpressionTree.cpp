/**
 * @file ExpressionTree.cpp
 * @brief Реализация классов для решения задачи CalcTree7
 */

#include "ExpressionTree.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <cctype>

using namespace std;

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

bool TreeNode::IsOperation() const {
    return value <= -1 && value >= -6;
}

shared_ptr<TreeNode> ExpressionTree::CreateNode(int val) const {
    return make_shared<TreeNode>(val);
}

int ExpressionTree::EvaluateSubtree(shared_ptr<TreeNode> node) const {
    if (!node->IsOperation()) {
        return node->value;
    }

    int left_val = EvaluateSubtree(node->left);
    int right_val = EvaluateSubtree(node->right);

    switch (node->value) {
        case ADD: return left_val + right_val;
        case SUB: return left_val - right_val;
        case MUL: return left_val * right_val;
        case DIV: return left_val / right_val;
        case MOD: return left_val % right_val;
        case POW: {
            int result = 1;
            for (int i = 0; i < right_val; ++i) result *= left_val;
            return result;
        }
        default: return 0;
    }
}

vector<int> ExpressionTree::ReadExpression(const string& file_name) const {
    ifstream file(file_name);
    if (!file) {
        cerr << "Не удалось открыть файл: " << file_name << endl;
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

shared_ptr<TreeNode> ExpressionTree::BuildTree(const vector<int>& tokens) {
    stack<shared_ptr<TreeNode>> st;

    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        int val = *it;
        auto node = CreateNode(val);

        if (node->IsOperation()) {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }

        st.push(node);
    }

    return st.top();
}

void ExpressionTree::TransformTree() {
    TransformTree(root);
}

void ExpressionTree::TransformTree(shared_ptr<TreeNode> node) {
    if (!node) return;

    TransformTree(node->left);
    TransformTree(node->right);

    if (node->IsOperation()) {
        int result = EvaluateSubtree(node);
        if (result >= 0 && result <= 9) {
            node->value = result;
            node->left = nullptr;
            node->right = nullptr;
        }
    }
}

void ExpressionTree::PrintPrefix() const {
    PrintPrefix(root);
    cout << endl;
}

void ExpressionTree::PrintPrefix(shared_ptr<TreeNode> node) const {
    if (!node) return;

    if (node->IsOperation()) {
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

    PrintPrefix(node->left);
    PrintPrefix(node->right);
}

ExpressionTree::ExpressionTree(const string& file_name) {
    root = BuildTree(ReadExpression(file_name));
}
