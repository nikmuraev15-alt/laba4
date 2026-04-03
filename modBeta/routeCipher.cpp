/**
 * @file routeCipher.cpp
 * @brief Реализация модуля маршрутной перестановки
 * @author Мураев Никита
 * @date 23.03.2026
 * @version 1.0
 */

#include "routeCipher.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <limits>

/**
 * @brief Конструктор RouteCipher
 * @param[in] key Ключ шифрования
 * @throw cipher_error если ключ невалидный
 */
RouteCipher::RouteCipher(int key)
{
    columns = getValidKey(key);
}

/**
 * @brief Шифрование методом маршрутной перестановки
 * @param[in] text Открытый текст
 * @return Зашифрованный текст
 * @throw cipher_error если текст невалидный
 * @details Алгоритм:
 *          1. Создается таблица rows×columns
 *          2. Текст записывается построчно слева направо
 *          3. Читается по столбцам справа налево, сверху вниз
 */
std::string RouteCipher::encrypt(const std::string& text)
{
    std::string validText = getValidOpenText(text);
    
    validateKeyTextRatio(validText.size());
    
    int original_length = validText.size();
    int rows = (original_length + columns - 1) / columns;

    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));
    int index = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (index < original_length) {
                table[i][j] = validText[index++];
            }
        }
    }

    std::string result;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

/**
 * @brief Дешифрование методом маршрутной перестановки
 * @param[in] text Зашифрованный текст
 * @return Расшифрованный текст
 * @throw cipher_error если шифротекст невалидный
 */
std::string RouteCipher::decrypt(const std::string& text)
{
    std::string validText = getValidCipherText(text);
    
    validateKeyTextRatio(validText.size());
    
    int encrypted_length = validText.size();
    int rows = (encrypted_length + columns - 1) / columns;
    
    int original_length = encrypted_length;
    
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));
    std::vector<std::vector<bool>> filled(rows, std::vector<bool>(columns, false));
    int original_index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (original_index < original_length) {
                filled[i][j] = true;
                original_index++;
            }
        }
    }
    
    int encrypted_index = 0;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (filled[i][j] && encrypted_index < encrypted_length) {
                table[i][j] = validText[encrypted_index++];
            }
        }
    }

    std::string result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (filled[i][j]) {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

/**
 * @brief Валидация ключа
 * @param[in] key Числовой ключ
 * @return Валидный ключ
 * @throw cipher_error если ключ невалидный
 */
int RouteCipher::getValidKey(int key)
{
    if (key <= 0) {
        throw cipher_error("Ключ должен быть положительным числом");
    }
    if (key > 50) {
        throw cipher_error("Слишком большой ключ (максимум 50)");
    }
    if (key == 1) {
        throw cipher_error("Ключ не может быть равен 1 (отсутствует перестановка)");
    }
    return key;
}

/**
 * @brief Проверка соотношения ключа и длины текста
 * @param[in] textLength Длина текста
 * @throw cipher_error если соотношение недопустимое
 */
void RouteCipher::validateKeyTextRatio(int textLength)
{
    if (columns >= textLength) {
        throw cipher_error("Ключ не должен быть больше или равен длине текста");
    }
    
    int recommendedMax = textLength / 3;
    if (columns > recommendedMax && textLength > 10) {
        throw cipher_error("Для лучшей безопасности ключ должен быть не больше 1/3 длины текста. "
                          "Максимум для этого текста: " + std::to_string(recommendedMax));
    }
    
    int rows = (textLength + columns - 1) / columns;
    if (rows < 2) {
        throw cipher_error("Слишком большой ключ для данного текста. "
                          "Уменьшите ключ чтобы получить хотя бы 2 строки в таблице");
    }
}

/**
 * @brief Валидация открытого текста
 * @param[in] text Исходный текст
 * @return Валидный текст
 * @throw cipher_error если текст невалидный
 */
std::string RouteCipher::getValidOpenText(const std::string& text)
{
    if (text.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    
    std::string result;
    
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        }
    }
    
    if (result.empty()) {
        throw cipher_error("Текст не содержит английские буквы");
    }
    
    if (result.length() < 4) {
        throw cipher_error("Текст слишком короткий для шифрования (минимум 4 символа)");
    }
    
    return result;
}

/**
 * @brief Валидация зашифрованного текста
 * @param[in] text Зашифрованный текст
 * @return Валидный шифротекст
 * @throw cipher_error если шифротекст невалидный
 */
std::string RouteCipher::getValidCipherText(const std::string& text)
{
    if (text.empty()) {
        throw cipher_error("Пустой шифротекст");
    }
    
    for (char c : text) {
        if (!isalpha(c)) {
            throw cipher_error("Шифротекст содержит недопустимые символы(должны быть только английские буквы)");
        }
        if (islower(c)) {
            throw cipher_error("Шифротекст должен содержать только прописные буквы");
        }
    }
    
    if (text.length() < 4) {
        throw cipher_error("Шифротекст слишком короткий");
    }
    
    return text;
}
