# Makefile для проекта шифра маршрутной перестановки
# Компилятор
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Исходные файлы
SOURCES = main.cpp routeCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = route_cipher

# Цели по умолчанию
all: $(TARGET)

# Главная программа
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Объектные файлы
main.o: main.cpp routeCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

routeCipher.o: routeCipher.cpp routeCipher.h
	$(CXX) $(CXXFLAGS) -c routeCipher.cpp

# Тестирование
test: $(TARGET)
	@echo "=== Тестирование шифра маршрутной перестановки ==="
	@echo "Программа готова к запуску: ./$(TARGET)"

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Отладочная сборка
debug: CXXFLAGS += -g
debug: clean $(TARGET)

# Справка
help:
	@echo "Доступные команды:"
	@echo "  make all       - компиляция программы"
	@echo "  make           - то же что и make all"
	@echo "  make test      - проверка сборки"
	@echo "  make clean     - удаление скомпилированных файлов"
	@echo "  make debug     - отладочная сборка"
	@echo "  make help      - эта справка"

.PHONY: all test clean debug help
