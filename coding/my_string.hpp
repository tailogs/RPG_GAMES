#include <iostream>
#include <cctype> // Для std::tolower и std::toupper
#include <sstream>
#include <string>

// Приведение строки к нижнему регистру
void toLowerCase(std::string&);

// Приведение строки к верхнему регистру
void toUpperCase(std::string&);

template <typename T>
std::string toString(const T&);