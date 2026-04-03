/**
 * @file modAlphaCipher.cpp
 * @brief Реализация модуля шифрования Гронсфельда
 * @details Содержит реализации методов класса modAlphaCipher
 * @author Мураев Никита
 * @date 23.03.2026
 * @version 1.0
 */

#include "modAlphaCipher.h"
#include <iostream>
#include <cwctype>

/**
 * @brief Конструктор класса modAlphaCipher
 * @param[in] skey Ключ шифрования
 * @throw cipher_error если ключ невалидный
 * @details Инициализирует алфавит и преобразует ключ в числовой вид
 */
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // Инициализируем алфавит (33 буквы с Ё)
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

/**
 * @brief Шифрование открытого текста
 * @param[in] open_text Открытый текст
 * @return Зашифрованный текст
 * @throw cipher_error если текст невалидный
 * @details Каждая буква текста сдвигается на позицию соответствующей буквы ключа
 */
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring valid_text = getValidOpenText(open_text);
    std::vector<int> work = convert(valid_text);
    int alpha_size = numAlpha.size();
    
    for (size_t i = 0; i < work.size(); i++) {
        int shift = key[i % key.size()];
        work[i] = (work[i] + shift + 1) % alpha_size;
    }
    return convert(work);
}

/**
 * @brief Дешифрование зашифрованного текста
 * @param[in] cipher_text Зашифрованный текст
 * @return Расшифрованный текст
 * @throw cipher_error если шифротекст невалидный
 * @details Выполняется обратный сдвиг букв текста
 */
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring valid_text = getValidCipherText(cipher_text);
    std::vector<int> work = convert(valid_text);
    int alpha_size = numAlpha.size();
    
    for (size_t i = 0; i < work.size(); i++) {
        int shift = key[i % key.size()];
        work[i] = (work[i] - shift - 1 + alpha_size * 2) % alpha_size;
    }
    return convert(work);
}

/**
 * @brief Преобразование строки в числовой вектор
 * @param[in] s Входная строка
 * @return Вектор индексов символов
 * @note Пробелы игнорируются
 */
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        if (c != L' ') {
            result.push_back(alphaNum[c]);
        }
    }
    return result;
}

/**
 * @brief Преобразование числового вектора в строку
 * @param[in] v Вектор индексов символов
 * @return Строка символов
 */
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

/**
 * @brief Валидация ключа шифрования
 * @param[in] s Исходный ключ
 * @return Валидный ключ
 * @throw cipher_error если ключ невалидный
 */
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    std::wstring tmp;
    for (auto c : s) {
        if (iswspace(c)) {
            throw cipher_error("Ключ содержит пробелы");
        }
        if (iswdigit(c)) {
            throw cipher_error("Ключ содержит цифры");
        }
        if (iswpunct(c)) {
            throw cipher_error("Ключ содержит знаки пунктуации");
        }
        if (iswalpha(c)) {
            wchar_t upper_c = towupper(c);
            if (alphaNum.find(upper_c) != alphaNum.end()) {
                tmp.push_back(upper_c);
            } else {
                throw cipher_error("Ключ содержит не русские буквы");
            }
        } else {
            throw cipher_error("Ключ содержит недопустимые символы");
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Ключ не содержит русских букв");
    }
    
    return tmp;
}

/**
 * @brief Валидация открытого текста
 * @param[in] s Исходный открытый текст
 * @return Валидный текст
 * @throw cipher_error если текст невалидный
 */
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            wchar_t upper_c = towupper(c);
            if (alphaNum.find(upper_c) != alphaNum.end()) {
                tmp.push_back(upper_c);
            } else {
                throw cipher_error("Текст содержит не русские буквы");
            }
        } else if (iswspace(c)) {
            tmp.push_back(c);
        } else {
            throw cipher_error("Текст содержит недопустимые символы (только русские буквы и пробелы)");
        }
    }
    
    bool has_letters = false;
    for (auto c : tmp) {
        if (iswalpha(c)) {
            has_letters = true;
            break;
        }
    }
    
    if (!has_letters) {
        throw cipher_error("Текст не содержит русских букв");
    }
    
    return tmp;
}

/**
 * @brief Валидация зашифрованного текста
 * @param[in] s Зашифрованный текст
 * @return Валидный шифротекст
 * @throw cipher_error если шифротекст невалидный
 */
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой шифротекст");
    }
    
    for (auto c : s) {
        if (iswspace(c)) {
            throw cipher_error("Шифротекст содержит пробелы");
        }
        if (alphaNum.find(c) == alphaNum.end()) {
            throw cipher_error("Шифротекст содержит недопустимые символы");
        }
    }
    
    return s;
}
