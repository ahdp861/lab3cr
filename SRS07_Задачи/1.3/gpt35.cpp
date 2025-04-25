/**
 * @file morse_code_functional.cpp
 * @brief Программа для преобразования текста в азбуку Морзе (функциональный стиль)
 * 
 * Реализация с использованием функционального подхода с лямбда-функциями и алгоритмами.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <numeric>

using namespace std;

/**
 * @brief Создает и возвращает таблицу кодов Морзе
 * @return unordered_map с соответствием символов и кодов Морзе
 */
auto createMorseMap() {
    return unordered_map<char, string>{
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

/**
 * @brief Основная функция преобразования строки в код Морзе
 * @param text Входная строка
 * @return Строка с кодом Морзе
 */
string convertToMorse(const string& text) {
    static const auto morseMap = createMorseMap();
    
    auto charToMorse = [](char c) {
        c = toupper(c);
        auto it = morseMap.find(c);
        return (it != morseMap.end()) ? it->second : "";
    };
    
    string result;
    bool first = true;
    
    for (char c : text) {
        string morse = charToMorse(c);
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
    cout << "Введите сообщение для преобразования в код Морзе: ";
    string input;
    getline(cin, input);
    
    string morse = convertToMorse(input);
    cout << "код Морзе: " << morse << endl;
    
    return 0;
}