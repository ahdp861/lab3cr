/**
 * @file CalcTree7.h
 * @brief Объявления функций и структур для решения задачи CalcTree7 (классический стиль)
 */

#ifndef CALCTREE7_H
#define CALCTREE7_H

#include <memory>
#include <vector>

/**
 * @brief Узел дерева выражения
 */
struct TreeNode {
    int value;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    /**
     * @brief Конструктор узла дерева
     * @param val Значение узла
     */
    explicit TreeNode(int val);
};

/**
 * @brief Создает новый узел дерева
 * @param val Значение узла
 * @return Указатель на созданный узел
 */
std::shared_ptr<TreeNode> createNode(int val);

/**
 * @brief Проверяет, является ли значение кодом операции
 * @param val Проверяемое значение
 * @return true если это операция, иначе false
 */
bool isOperation(int val);

/**
 * @brief Читает выражение из файла
 * @param filename Имя файла
 * @return Вектор токенов выражения
 */
std::vector<int> readExpression(const std::string& filename);

/**
 * @brief Строит дерево выражения из префиксной формы
 * @param tokens Вектор токенов
 * @return Указатель на корень дерева
 */
std::shared_ptr<TreeNode> buildTree(const std::vector<int>& tokens);

/**
 * @brief Вычисляет значение поддерева
 * @param node Корень поддерева
 * @return Значение поддерева
 */
int evaluateSubtree(std::shared_ptr<TreeNode> node);

/**
 * @brief Преобразует дерево, заменяя поддеревья с результатами 0-9 на листья
 * @param node Корень дерева
 */
void transformTree(std::shared_ptr<TreeNode> node);

/**
 * @brief Выводит дерево в префиксной форме
 * @param node Корень дерева
 */
void printPrefix(std::shared_ptr<TreeNode> node);

#endif // CALCTREE7_H
