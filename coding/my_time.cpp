#include "my_time.hpp"

std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char buffer[10];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
    return std::string(buffer);
}