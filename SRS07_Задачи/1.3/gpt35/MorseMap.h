/**
 * @file MorseMap.h
 * @brief Заголовочный файл с функцией создания таблицы кодов Морзе
 */

#ifndef MORSEMAP_H
#define MORSEMAP_H

#include <unordered_map>
#include <string>

/**
 * @brief Создает и возвращает таблицу кодов Морзе
 * @return unordered_map с соответствием символов и кодов Морзе
 */
std::unordered_map<char, std::string> createMorseMap();

#endif // MORSEMAP_H
