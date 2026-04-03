# Компилятор
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Исходные файлы
SOURCES = main.cpp modAlphaCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = gronsfeld_cipher

# Цели по умолчанию
all: $(TARGET)

# Главная программа
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Объектные файлы
main.o: main.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

modAlphaCipher.o: modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c modAlphaCipher.cpp

# Тестирование
test: $(TARGET)
	@echo "=== Тестирование шифра Гронсфельда ==="
	@./$(TARGET)

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
	@echo "  make test      - запуск теста"
	@echo "  make clean     - удаление скомпилированных файлов"
	@echo "  make debug     - отладочная сборка"
	@echo "  make help      - эта справка"

.PHONY: all test clean debug help
