/**
 * @file main.cpp
 * @brief Точка входа в программу решения задачи CalcTree7 (классический стиль)
 */

#include <iostream>
#include "CalcTree7.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    std::vector<int> tokens = readExpression(argv[1]);
    std::shared_ptr<TreeNode> root = buildTree(tokens);

    std::cout << "Исходное дерево (префиксная форма): ";
    printPrefix(root);
    std::cout << std::endl;

    transformTree(root);

    std::cout << "Преобразованное дерево (префиксная форма): ";
    printPrefix(root);
    std::cout << std::endl;

    return 0;
}
