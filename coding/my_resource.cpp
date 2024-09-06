#include "my_resource.hpp"

// Получение пути к ресурсу на основе типа файла
std::string getResource(std::string name, std::string type_file)
{
    toLowerCase(type_file); // Приведение типа файла к нижнему регистру
    if (type_file == "img")
        return "resource/img/" + name; // Путь для изображений
    else if (type_file == "fonts")
        return "resource/fonts/" + name; // Путь для шрифтов
    else
        exit(1); // Завершение программы, если тип не поддерживается
}