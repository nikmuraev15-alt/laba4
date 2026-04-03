/**
 * @file main.cpp
 * @brief Главный модуль программы шифрования Гронсфельда
 * @details Содержит пользовательский интерфейс для работы с шифром Гронсфельда
 * @author Мураев Никита
 * @date 23.03.2026
 * @version 1.0
 */

#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include "modAlphaCipher.h"

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении, 1 при ошибке
 * @details Обеспечивает взаимодействие с пользователем:
 *          - Ввод ключа шифрования
 *          - Ввод текста для шифрования
 *          - Шифрование и вывод результата
 *          - Дешифрование и проверка результата
 */
int main()
{
    // Установка локали для поддержки русского языка
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    try {
        std::wstring key, text;
        
        // Ввод ключа
        std::wcout << L"Введите ключ (русские буквы): ";
        std::getline(std::wcin, key);
        
        // Создание объекта шифратора
        modAlphaCipher cipher(key);
        
        // Ввод текста для шифрования
        std::wcout << L"Введите текст для шифрования: ";
        std::getline(std::wcin, text);

        std::wcout << L"Исходный текст: " << text << std::endl;
        
        // Шифрование
        std::wstring encrypted = cipher.encrypt(text);
        std::wcout << L"Зашифрованный текст: " << encrypted << std::endl;
        
        // Дешифрование
        std::wstring decrypted = cipher.decrypt(encrypted);
        std::wcout << L"Расшифрованный текст: " << decrypted << std::endl;
        
    } catch (const cipher_error& e) {
        std::cerr << "Ошибка шифрования: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
