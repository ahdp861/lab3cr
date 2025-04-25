/**
 * @file MorseConverter.cpp
 * @brief Реализация класса MorseConverter для преобразования текста в азбуку Морзе
 */

#include "MorseConverter.h"
#include <cctype>

void MorseConverter::initializeMap() {
    morseMap = {
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
}

MorseConverter::MorseConverter() {
    initializeMap();
}

std::string MorseConverter::convertChar(char c) const {
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    auto it = morseMap.find(c);
    if (it != morseMap.end()) {
        return it->second;
    }
    return "";
}

std::string MorseConverter::convertString(const std::string& text) const {
    std::string result;
    for (char c : text) {
        std::string morse = convertChar(c);
        if (!morse.empty()) {
            if (!result.empty() && result.back() != ' ') {
                result += " ";
            }
            result += morse;
        }
    }
    return result;
}
