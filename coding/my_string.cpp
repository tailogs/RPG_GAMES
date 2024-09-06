#include "my_string.hpp" 

// Приведение строки к нижнему регистру
void toLowerCase(std::string& str) {
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c)); // Приведение каждого символа к нижнему регистру
    }
}

// Приведение строки к верхнему регистру
void toUpperCase(std::string& str) {
    for (char& c : str) {
        c = std::toupper(static_cast<unsigned char>(c)); // Приведение каждого символа к верхнему регистру
    }
}

template <typename T>
std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}