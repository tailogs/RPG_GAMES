# Объявление переменных
CXX = g++
CXXFLAGS = -Isrc/include
LDFLAGS = -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
RESOURCES = resources.o
TARGET = main.exe

# Целевая цель по умолчанию
all: compile link

# Компиляция исходных файлов
compile:
	$(CXX) $(CXXFLAGS) -c coding/*.cpp
	windres resource.rc -o $(RESOURCES)

# Линковка объектных файлов и ресурсов
link:
	$(CXX) *.o $(RESOURCES) -o $(TARGET) $(LDFLAGS)

# Очистка промежуточных файлов и сгенерированных файлов
clean:
	del *.o $(RESOURCES) $(TARGET)

# Запуск исполняемого файла
run: all
	$(TARGET)

.PHONY: all compile link clean run
