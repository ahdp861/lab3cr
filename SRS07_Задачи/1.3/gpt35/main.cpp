/**
 * @file main.cpp
 * @brief Точка входа в программу для преобразования текста в азбуку Морзе
 */

#include <iostream>
#include <string>
#include <cctype>
#include "MorseMap.h"

/**
 * @brief Основная функция преобразования строки в код Морзе
 * @param text Входная строка
 * @return Строка с кодом Морзе
 */
std::string convertToMorse(const std::string& text) {
    static const auto morseMap = createMorseMap();
    
    auto charToMorse = [](char c) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        auto it = morseMap.find(c);
        return (it != morseMap.end()) ? it->second : "";
    };
    
    std::string result;
    bool first = true;
    
    for (char c : text) {
        std::string morse = charToMorse(c);
        if (!morse.empty()) {
            if (!first && morse != " ") {
                result += " ";
            }
            result += morse;
            first = (morse == " ");
        }
    }
    
    return result;
}

int main() {
    std::cout << "Введите сообщение для преобразования в код Морзе: ";
    std::string input;
    std::getline(std::cin, input);
    
    std::string morse = convertToMorse(input);
    std::cout << "код Морзе: " << morse << std::endl;
    
    return 0;
}
