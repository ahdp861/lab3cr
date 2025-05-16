/**
 * @file main.cpp
 * @brief Точка входа в программу решения задачи CalcTree7
 */

#include <iostream>
#include "ExpressionTree.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    ExpressionTree tree(argv[1]);

    std::cout << "Исходное дерево (префиксная форма): ";
    tree.PrintPrefix();

    tree.TransformTree();

    std::cout << "Преобразованное дерево (префиксная форма): ";
    tree.PrintPrefix();

    return 0;
}
