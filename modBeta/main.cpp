/**
 * @file main.cpp
 * @brief Главный модуль программы маршрутной перестановки
 * @details Содержит интерактивный пользовательский интерфейс
 * @author Мураев Никита
 * @date 23.03.2026
 * @version 1.0
 */

#include <iostream>
#include <limits>
#include "routeCipher.h"

/**
 * @brief Функция для безопасного ввода целого числа
 * @return Введенное целое число
 * @details Обрабатывает некорректный ввод и очищает буфер
 */
int getValidIntegerInput() {
    int value;
    while (true) {
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите целое число: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении, 1 при ошибке
 * @details Реализует интерактивное меню:
 *          - Ввод ключа (количество столбцов)
 *          - Выбор операции (шифрование/дешифрование)
 *          - Обработка текста
 *          - Обработка исключений
 */
int main()
{
    try {
        int key;
        std::string text;
        
        std::cout << "Введите ключ (число столбцов): ";
        key = getValidIntegerInput();
        
        RouteCipher cipher(key);

        int op;
        do {
            std::cout << "Операция (0-выход, 1-шифровать, 2-расшифровать): ";
            
            while (!(std::cin >> op) || (op != 0 && op != 1 && op != 2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: введите 0, 1 или 2: ";
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (op == 1 || op == 2) {
                std::cout << "Введите текст: ";
                std::getline(std::cin, text);
                
                try {
                    if (op == 1) {
                        std::cout << "Зашифрованный текст: " << cipher.encrypt(text) << std::endl;
                    } else {
                        std::cout << "Расшифрованный текст: " << cipher.decrypt(text) << std::endl;
                    }
                } catch (const cipher_error& e) {
                    std::cerr << "Ошибка шифрования: " << e.what() << std::endl;
                }
            }
        } while (op != 0);
        
    } catch (const cipher_error& e) {
        std::cerr << "Ошибка инициализации: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
