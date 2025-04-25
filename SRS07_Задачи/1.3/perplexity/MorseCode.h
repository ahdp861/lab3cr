/**
 * @file MorseCode.h
 * @brief Объявление функций и таблицы для преобразования текста в азбуку Морзе (классический стиль)
 */

#ifndef MORSECODE_H
#define MORSECODE_H

#include <string>

/**
 * @brief Преобразует символ в код Морзе
 * @param c Входной символ
 * @return Строка с кодом Морзе или пустая строка, если символ не найден
 */
std::string charToMorse(char c);

/**
 * @brief Преобразует строку в код Морзе
 * @param text Входная строка
 * @return Строка с кодом Морзе
 */
std::string stringToMorse(const std::string& text);

#endif // MORSECODE_H
