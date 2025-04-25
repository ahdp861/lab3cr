/**
 * @file main.cpp
 * @brief Точка входа в программу для преобразования текста в азбуку Морзе
 */

#include <iostream>
#include <string>
#include "MorseConverter.h"

int main() {
    MorseConverter converter;

    std::cout << "Введите сообщение для преобразования в код Морзе: ";
    std::string input;
    std::getline(std::cin, input);

    std::string morse = converter.convertString(input);
    std::cout << "Код Морзе: " << morse << std::endl;

    return 0;
}
