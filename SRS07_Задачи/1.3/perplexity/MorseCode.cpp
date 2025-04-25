/**
 * @file MorseCode.cpp
 * @brief Реализация функций для преобразования текста в азбуку Морзе 
 */

#include "MorseCode.h"
#include <unordered_map>
#include <cctype>

// Таблица соответствия русских букв и кода Морзе
static const std::unordered_map<char, std::string> morseCode = {
    {'А', ".-"}, {'Б', "-..."}, {'В', ".--"}, {'Г', "--."},
    {'Д', "-.."}, {'Е', "."}, {'Ж', "...-"}, {'З', "--.."},
    {'И', ".."}, {'Й', ".---"}, {'К', "-.-"}, {'Л', ".-.."},
    {'М', "--"}, {'Н', "-."}, {'О', "---"}, {'П', ".--."},
    {'Р', ".-."}, {'С', "..."}, {'Т', "-"}, {'У', "..-"},
    {'Ф', "..-."}, {'Х', "...."}, {'Ц', "-.-."}, {'Ч', "---."},
    {'Ш', "----"}, {'Щ', "--.-"}, {'Ъ', "--.--"}, {'Ы', "-.--"},
    {'Ь', "-..-"}, {'Э', "..-.."}, {'Ю', "..--"}, {'Я', ".-.-"},
    {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."},
    {'9', "----."}, {'0', "-----"}, {' ', " "}
};

std::string charToMorse(char c) {
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    auto it = morseCode.find(c);
    if (it != morseCode.end()) {
        return it->second;
    }
    return ""; // Неизвестные символы игнорируются
}

std::string stringToMorse(const std::string& text) {
    std::string result;
    for (char c : text) {
        std::string morse = charToMorse(c);
        if (!morse.empty()) {
            if (!result.empty() && result.back() != ' ') {
                result += " ";
            }
            result += morse;
        }
    }
    return result;
}
