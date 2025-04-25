/**
 * @file calctree7_oop.cpp
 * @brief Решение задачи CalcTree7 (ООП стиль)
 * 
 * Реализация с использованием классов ExpressionTree и TreeNode для представления
 * дерева выражений и операций над ним.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <memory>
#include <cctype>

using namespace std;

// Коды операций
enum Operation {
    ADD = -1,
    SUB = -2,
    MUL = -3,
    DIV = -4,
    MOD = -5,
    POW = -6
};

/**
 * @brief Узел дерева выражения
 */
class TreeNode {
public:
    int value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    
    /**
     * @brief Проверяет, является ли узел операцией
     * @return true если узел представляет операцию, иначе false
     */
    bool isOperation() const {
        return value <= -1 && value >= -6;
    }
};

/**
 * @brief Класс для работы с деревом выражений
 */
class ExpressionTree {
private:
    shared_ptr<TreeNode> root;
    
    /**
     * @brief Создает новый узел дерева
     * @param val Значение узла
     * @return Указатель на созданный узел
     */
    shared_ptr<TreeNode> createNode(int val) const {
        return make_shared<TreeNode>(val);
    }
    
    /**
     * @brief Вычисляет значение поддерева
     * @param node Корень поддерева
     * @return Значение поддерева
     */
    int evaluateSubtree(shared_ptr<TreeNode> node) const {
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
    
public:
    /**
     * @brief Конструктор ExpressionTree
     * @param filename Имя файла с выражением
     */
    ExpressionTree(const string& filename) {
        root = buildTree(readExpression(filename));
    }
    
    /**
     * @brief Читает выражение из файла
     * @param filename Имя файла
     * @return Вектор токенов выражения
     */
    vector<int> readExpression(const string& filename) const {
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
    }
    
    /**
     * @brief Строит дерево выражения из префиксной формы
     * @param tokens Вектор токенов
     * @return Указатель на корень дерева
     */
    shared_ptr<TreeNode> buildTree(const vector<int>& tokens) {
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
    
    /**
     * @brief Преобразует дерево, заменяя поддеревья с результатами 0-9 на листья
     */
    void transformTree() {
        transformTree(root);
    }
    
    /**
     * @brief Рекурсивная функция преобразования дерева
     * @param node Текущий узел
     */
    void transformTree(shared_ptr<TreeNode> node) {
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
    
    /**
     * @brief Выводит дерево в префиксной форме
     */
    void printPrefix() const {
        printPrefix(root);
        cout << endl;
    }
    
    /**
     * @brief Рекурсивная функция вывода дерева
     * @param node Текущий узел
     */
    void printPrefix(shared_ptr<TreeNode> node) const {
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
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " filename" << endl;
        return 1;
    }
    
    ExpressionTree tree(argv[1]);
    
    cout << "Исходное дерево (префиксная форма): ";
    tree.printPrefix();
    
    tree.transformTree();
    
    cout << "Преобразованное дерево (префиксная форма): ";
    tree.printPrefix();
    
    return 0;
}