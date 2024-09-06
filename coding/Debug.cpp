#include "Debug.hpp"

// Конструктор
Debug::Debug() {
    // Генерация палитры при создании объекта класса
    colorPalette = generateColorPalette();
}

// Статический метод для отрисовки декораций линий
void Debug::drawLineDecoration(sf::RenderWindow& window, const Chunk& chunk, const sf::Vector2f& heroPosition, sf::Font& font) {
    if (chunk.treeDecorations.empty() && chunk.decorations.empty()) {
        // Декорации не загружены
        return;
    }

    int lineIndex = 1;

    // Отрисовываем линии от героя ко всем декорациям деревьев
    for (const auto& treePosition : chunk.treeDecorations) {
        float distance = calculateDistance(heroPosition, treePosition);
        drawLineWithText(window, heroPosition, treePosition, lineIndex++, distance, font, sf::Color::Red);

        // Отрисовка границ для декорации дерева
        drawBoundary(window, treePosition, sf::Color::Red);
    }

    // Отрисовываем линии от героя ко всем остальным декорациям
    for (int y = 0; y < CHUNK_SIZE; ++y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            const sf::Sprite& decoration = chunk.decorations[y][x];
            if (decoration.getTexture() != nullptr) {
                sf::Vector2f decorationPos = decoration.getPosition();
                sf::Vector2f center = decorationPos + sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2);
                float distance = calculateDistance(heroPosition, center);
                drawLineWithText(window, heroPosition, center, lineIndex++, distance, font, sf::Color::Green);

                // Отрисовка границ для декорации
                drawBoundary(window, decorationPos, sf::Color::Green);
            }
        }
    }
}

// Приватные методы
std::vector<sf::Color> Debug::generateColorPalette() {
    std::vector<sf::Color> palette(1024);

    for (int i = 0; i < 256; ++i) {
        int r = i;
        int g = 255 - i;
        int b = (i < 128) ? 2 * i : 255 - 2 * (i - 128);
        palette[i] = sf::Color(r, g, b);
    }

    for (int i = 256; i < 512; ++i) {
        int r = 255 - (i - 256);
        int g = (i - 256) * 2;
        int b = 255 - r;
        palette[i] = sf::Color(r, g, b);
    }

    for (int i = 512; i < 768; ++i) {
        int r = (i - 512) * 2;
        int g = 255 - (i - 512);
        int b = 255;
        palette[i] = sf::Color(r, g, b);
    }

    for (int i = 768; i < 1024; ++i) {
        int r = 255;
        int g = (i - 768) * 2;
        int b = 255 - (i - 768);
        palette[i] = sf::Color(r, g, b);
    }

    return palette;
}

sf::Color Debug::getColorForDistance(float distance) {
    const float maxDistance = 1920.0f / 2;  // Половина ширины экрана
    float normalizedDistance = std::min(distance / maxDistance, 1.0f);
    int colorIndex = static_cast<int>(normalizedDistance * (colorPalette.size() - 1));
    return colorPalette[colorIndex];
}

void Debug::drawLineWithText(sf::RenderWindow& window, const sf::Vector2f& start, const sf::Vector2f& end, int index, float distance, sf::Font& font, const sf::Color& boundaryColor) {
    sf::Color lineColor = getColorForDistance(distance);

    // Отрисовка линии
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = start;
    line[0].color = lineColor;
    line[1].position = end;
    line[1].color = lineColor;
    window.draw(line);

    // Отрисовка текста с расстоянием
    drawText(window, std::to_string(static_cast<int>(distance)), font, lineColor, (start.x + end.x) / 2, (start.y + end.y) / 2);

    // Отрисовка номера линии
    drawText(window, std::to_string(index), font, lineColor, start.x, start.y);
}

void Debug::drawBoundary(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Color& color) {
    sf::RectangleShape boundary(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    boundary.setPosition(position);
    boundary.setOutlineColor(color);
    boundary.setOutlineThickness(2);
    boundary.setFillColor(sf::Color::Transparent);
    window.draw(boundary);
}

void Debug::drawText(sf::RenderWindow& window, const std::string& text, sf::Font& font, const sf::Color& color, float x, float y) {
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setString(text);
    displayText.setCharacterSize(24);
    displayText.setFillColor(color);
    displayText.setPosition(x, y);
    window.draw(displayText);
}

float Debug::calculateDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB) {
    return std::sqrt(std::pow(pointB.x - pointA.x, 2) + std::pow(pointB.y - pointA.y, 2));
}