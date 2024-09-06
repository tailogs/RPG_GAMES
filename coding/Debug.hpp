#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Chunk.hpp"  // Предполагается, что Chunk объявлен в этом заголовке

class Debug {
public:
    // Конструктор
    Debug();

    // Метод для отрисовки декораций линий
    void drawLineDecoration(sf::RenderWindow& window, const Chunk& chunk, const sf::Vector2f& heroPosition, sf::Font& font);

private:
    // Приватные методы и переменные
    std::vector<sf::Color> colorPalette;

    // Генерация палитры цветов
    std::vector<sf::Color> generateColorPalette();

    // Получение цвета по расстоянию
    sf::Color getColorForDistance(float distance);

    // Отрисовка линии с текстом
    void drawLineWithText(sf::RenderWindow& window, const sf::Vector2f& start, const sf::Vector2f& end, int index, float distance, sf::Font& font, const sf::Color& boundaryColor);

    // Отрисовка границы для декорации
    void drawBoundary(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Color& color);

    // Отрисовка текста
    void drawText(sf::RenderWindow& window, const std::string& text, sf::Font& font, const sf::Color& color, float x, float y);

    // Вычисление расстояния между двумя точками
    float calculateDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB);
};

#endif // DEBUG_HPP
