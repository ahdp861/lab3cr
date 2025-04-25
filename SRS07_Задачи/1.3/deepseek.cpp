/**
 * @file morse_code_oop.cpp
 * @brief Программа для преобразования текста в азбуку Морзе (ООП стиль)
 * 
 * Реализация с использованием объектно-ориентированного подхода с классом MorseConverter, содержащим
 * логику преобразования
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

class MorseConverter {
private:
    unordered_map<char, string> morseMap;
    
    void initializeMap() {
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

public:
    /**
     * @brief Конструктор MorseConverter
     */
    MorseConverter() {
        initializeMap();
    }
    
    /**
     * @brief Преобразует символ в код Морзе
     * @param c Входной символ
     * @return Строка с кодом Морзе или пустая строка, если символ не найден
     */
    string convertChar(char c) const {
        c = toupper(c);
        auto it = morseMap.find(c);
        if (it != morseMap.end()) {
            return it->second;
        }
        return "";
    }
    
    /**
     * @brief Преобразует строку в код Морзе
     * @param text Входная строка
     * @return Строка с кодом Морзе
     */
    string convertString(const string& text) const {
        string result;
        for (char c : text) {
            string morse = convertChar(c);
            if (!morse.empty()) {
                if (!result.empty() && result.back() != ' ') {
                    result += " ";
                }
                result += morse;
            }
        }
        return result;
    }
};

int main() {
    MorseConverter converter;
    
    cout << "Введите сообщение для преобразования в код Морзе: ";
    string input;
    getline(cin, input);
    
    string morse = converter.convertString(input);
    cout << "код Морзе: " << morse << endl;
    
    return 0;
}