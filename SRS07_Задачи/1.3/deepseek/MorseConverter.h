/**
 * @file MorseConverter.h
 * @brief Класс для преобразования текста в азбуку Морзе 
 * 
 * Содержит объявление класса MorseConverter, который реализует логику преобразования символов и строк в код Морзе.
 */

#ifndef MORSECONVERTER_H
#define MORSECONVERTER_H

#include <string>
#include <unordered_map>

class MorseConverter {
private:
    std::unordered_map<char, std::string> morseMap;

    /**
     * @brief Инициализация словаря соответствия символов и кода Морзе
     */
    void initializeMap();

public:
    /**
     * @brief Конструктор MorseConverter
     */
    MorseConverter();

    /**
     * @brief Преобразует символ в код Морзе
     * @param c Входной символ
     * @return Строка с кодом Морзе или пустая строка, если символ не найден
     */
    std::string convertChar(char c) const;

    /**
     * @brief Преобразует строку в код Морзе
     * @param text Входная строка
     * @return Строка с кодом Морзе
     */
    std::string convertString(const std::string& text) const;
};

#endif // MORSECONVERTER_H
