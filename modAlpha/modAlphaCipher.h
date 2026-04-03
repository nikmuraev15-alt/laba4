/**
 * @file modAlphaCipher.h
 * @brief Заголовочный файл для модуля шифрования Гронсфельда
 * @details Содержит объявления классов для шифрования и дешифрования текста 
 *          методом Гронсфельда на русском языке
 * @author Мураев Никита
 * @date 23.03.2026
 * @version 1.0
 * @copyright Учебный проект
 * @warning Реализация только для русского языка
 */

#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <stdexcept>

/**
 * @class cipher_error
 * @brief Класс исключения для ошибок шифрования
 * @details Наследуется от std::invalid_argument, используется для обработки 
 *          ошибок в процессе шифрования/дешифрования
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с std::string в качестве параметра
     * @param[in] what_arg Сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор с C-строкой в качестве параметра
     * @param[in] what_arg Сообщение об ошибке (C-строка)
     */
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

/**
 * @class modAlphaCipher
 * @brief Класс для шифрования методом Гронсфельда
 * @details Реализует шифрование и дешифрование текста на русском языке
 *          с использованием ключа-строки. Поддерживает русский алфавит (33 буквы).
 *          Алгоритм: каждая буква текста сдвигается на позицию соответствующей
 *          буквы ключа по модулю 33.
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";  ///< Алфавит для шифрования (33 буквы)
    std::map<wchar_t, int> alphaNum;  ///< Ассоциативный массив "символ -> индекс в алфавите"
    std::vector<int> key;  ///< Ключ шифрования в числовом виде
    
    /**
     * @brief Преобразование строки в числовой вектор
     * @param[in] s Входная строка
     * @return Вектор индексов символов в алфавите
     * @note Пробелы игнорируются
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Преобразование числового вектора в строку
     * @param[in] v Вектор индексов символов
     * @return Строка символов
     */
    std::wstring convert(const std::vector<int>& v);
    
    /**
     * @brief Валидация и нормализация ключа шифрования
     * @param[in] s Исходный ключ
     * @return Валидный ключ (в верхнем регистре, только русские буквы)
     * @throw cipher_error если ключ пустой, содержит пробелы, цифры, 
     *        знаки пунктуации или не русские буквы
     */
    std::wstring getValidKey(const std::wstring& s);
    
    /**
     * @brief Валидация открытого текста
     * @param[in] s Исходный открытый текст
     * @return Валидный текст (русские буквы в верхнем регистре, пробелы сохраняются)
     * @throw cipher_error если текст пустой, не содержит русских букв или 
     *        содержит недопустимые символы
     */
    std::wstring getValidOpenText(const std::wstring& s);
    
    /**
     * @brief Валидация зашифрованного текста
     * @param[in] s Зашифрованный текст
     * @return Валидный шифротекст
     * @throw cipher_error если текст пустой, содержит пробелы или 
     *        недопустимые символы
     */
    std::wstring getValidCipherText(const std::wstring& s);

public:
    /**
     * @brief Удаленный конструктор по умолчанию
     * @details Запрещено создание объекта без ключа
     */
    modAlphaCipher() = delete;
    
    /**
     * @brief Конструктор с ключом шифрования
     * @param[in] skey Ключ шифрования (строка русских букв)
     * @throw cipher_error если ключ невалидный
     * @note Ключ будет преобразован к верхнему регистру и провалидирован
     */
    modAlphaCipher(const std::wstring& skey);
    
    /**
     * @brief Шифрование открытого текста
     * @param[in] open_text Открытый текст для шифрования
     * @return Зашифрованный текст
     * @throw cipher_error если текст невалидный
     * @details Строчные буквы преобразуются в прописные, не-буквы удаляются
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Дешифрование зашифрованного текста
     * @param[in] cipher_text Зашифрованный текст
     * @return Расшифрованный текст
     * @throw cipher_error если шифротекст невалидный
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};
