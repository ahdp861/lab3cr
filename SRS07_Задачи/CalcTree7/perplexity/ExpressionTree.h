/**
 * @file ExpressionTree.h
 * @brief Объявление классов для решения задачи CalcTree7 (ООП стиль)
 */

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <memory>
#include <string>
#include <vector>

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
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    /**
     * @brief Конструктор узла дерева
     * @param val Значение узла
     */
    explicit TreeNode(int val);

    /**
     * @brief Проверяет, является ли узел операцией
     * @return true если узел представляет операцию, иначе false
     */
    bool isOperation() const;
};

/**
 * @brief Класс для работы с деревом выражений
 */
class ExpressionTree {
private:
    std::shared_ptr<TreeNode> root;

    /**
     * @brief Создает новый узел дерева
     * @param val Значение узла
     * @return Указатель на созданный узел
     */
    std::shared_ptr<TreeNode> createNode(int val) const;

    /**
     * @brief Вычисляет значение поддерева
     * @param node Корень поддерева
     * @return Значение поддерева
     */
    int evaluateSubtree(std::shared_ptr<TreeNode> node) const;

    /**
     * @brief Рекурсивная функция преобразования дерева
     * @param node Текущий узел
     */
    void transformTree(std::shared_ptr<TreeNode> node);

    /**
     * @brief Рекурсивная функция вывода дерева
     * @param node Текущий узел
     */
    void printPrefix(std::shared_ptr<TreeNode> node) const;

public:
    /**
     * @brief Конструктор ExpressionTree
     * @param filename Имя файла с выражением
     */
    explicit ExpressionTree(const std::string& filename);

    /**
     * @brief Читает выражение из файла
     * @param filename Имя файла
     * @return Вектор токенов выражения
     */
    std::vector<int> readExpression(const std::string& filename) const;

    /**
     * @brief Строит дерево выражения из префиксной формы
     * @param tokens Вектор токенов
     * @return Указатель на корень дерева
     */
    std::shared_ptr<TreeNode> buildTree(const std::vector<int>& tokens);

    /**
     * @brief Преобразует дерево, заменяя поддеревья с результатами 0-9 на листья
     */
    void transformTree();

    /**
     * @brief Выводит дерево в префиксной форме
     */
    void printPrefix() const;
};

#endif // EXPRESSIONTREE_H
