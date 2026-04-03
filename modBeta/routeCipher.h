/**
 * @file routeCipher.h
 * @brief Заголовочный файл для модуля маршрутной перестановки
 * @details Содержит объявления классов для шифрования табличной маршрутной перестановкой
 * @author Мураев Никита
 * @date 23.03.2026
 * @version 1.0
 * @copyright Учебный проект
 */

#pragma once
#include <string>
#include <vector>
#include <stdexcept>

/**
 * @class cipher_error
 * @brief Класс исключения для ошибок шифрования (маршрутная перестановка)
 * @details Наследуется от std::invalid_argument
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с std::string
     * @param[in] what_arg Сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор с C-строкой
     * @param[in] what_arg Сообщение об ошибке
     */
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

/**
 * @class RouteCipher
 * @brief Класс для шифрования методом маршрутной перестановки
 * @details Реализует табличную маршрутную перестановку:
 *          - Запись: по строкам слева направо, сверху вниз
 *          - Чтение: по столбцам сверху вниз, справа налево
 *          Ключ - количество столбцов таблицы
 */
class RouteCipher
{
private:
    int columns;  ///< Количество столбцов (ключ шифрования)
    
    /**
     * @brief Валидация ключа
     * @param[in] key Числовой ключ
     * @return Валидный ключ
     * @throw cipher_error если ключ невалидный
     */
    int getValidKey(int key);
    
    /**
     * @brief Проверка соотношения ключа и длины текста
     * @param[in] textLength Длина текста
     * @throw cipher_error если соотношение недопустимое
     */
    void validateKeyTextRatio(int textLength);
    
    /**
     * @brief Валидация открытого текста
     * @param[in] text Исходный текст
     * @return Валидный текст
     * @throw cipher_error если текст невалидный
     */
    std::string getValidOpenText(const std::string& text);
    
    /**
     * @brief Валидация зашифрованного текста
     * @param[in] text Зашифрованный текст
     * @return Валидный шифротекст
     * @throw cipher_error если шифротекст невалидный
     */
    std::string getValidCipherText(const std::string& text);
    
public:
    /**
     * @brief Удаленный конструктор по умолчанию
     */
    RouteCipher() = delete;
    
    /**
     * @brief Конструктор с ключом
     * @param[in] key Ключ шифрования (количество столбцов)
     * @throw cipher_error если ключ невалидный
     */
    RouteCipher(int key);
    
    /**
     * @brief Шифрование текста
     * @param[in] text Открытый текст
     * @return Зашифрованный текст
     * @throw cipher_error если текст невалидный
     */
    std::string encrypt(const std::string& text);
    
    /**
     * @brief Дешифрование текста
     * @param[in] text Зашифрованный текст
     * @return Расшифрованный текст
     * @throw cipher_error если шифротекст невалидный
     */
    std::string decrypt(const std::string& text);
};
