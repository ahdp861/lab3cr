/**
 * @file main.cpp
 * @brief Точка входа в программу для преобразования текста в азбуку Морзе (классический стиль)
 */

#include <iostream>
#include <string>
#include "MorseCode.h"

int main() {
    std::cout << "Введите сообщение для преобразования в код Морзе: ";
    std::string input;
    std::getline(std::cin, input);
    
    std::string morse = stringToMorse(input);
    std::cout << "Код Морзе: " << morse << std::endl;
    
    return 0;
}
