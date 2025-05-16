/**
 * @file ExpressionTree.h
 * @brief Объявление классов для решения задачи CalcTree7
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
    bool IsOperation() const;
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
    std::shared_ptr<TreeNode> CreateNode(int val) const;

    /**
     * @brief Вычисляет значение поддерева
     * @param node Корень поддерева
     * @return Значение поддерева
     */
    int EvaluateSubtree(std::shared_ptr<TreeNode> node) const;

    /**
     * @brief Рекурсивная функция преобразования дерева
     * @param node Текущий узел
     */
    void TransformTree(std::shared_ptr<TreeNode> node);

    /**
     * @brief Рекурсивная функция вывода дерева
     * @param node Текущий узел
     */
    void PrintPrefix(std::shared_ptr<TreeNode> node) const;

public:
    /**
     * @brief Конструктор ExpressionTree
     * @param file_name Имя файла с выражением
     */
    explicit ExpressionTree(const std::string& file_name);

    /**
     * @brief Читает выражение из файла
     * @param file_name Имя файла
     * @return Вектор токенов выражения
     */
    std::vector<int> ReadExpression(const std::string& file_name) const;

    /**
     * @brief Строит дерево выражения из префиксной формы
     * @param tokens Вектор токенов
     * @return Указатель на корень дерева
     */
    std::shared_ptr<TreeNode> BuildTree(const std::vector<int>& tokens);

    /**
     * @brief Преобразует дерево, заменяя поддеревья с результатами 0-9 на листья
     */
    void TransformTree();

    /**
     * @brief Выводит дерево в префиксной форме
     */
    void PrintPrefix() const;
};

#endif // EXPRESSIONTREE_H
