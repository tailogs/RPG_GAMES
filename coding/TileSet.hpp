#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Globals.hpp"
#include "my_resource.hpp"

// Структура для спрайтов плиток
struct TileSet {
    sf::Texture texture;
    std::vector<sf::Sprite> sprites;
};

// Структура для хранения информации о плитке
struct Tile {
    int type;
    int spriteIndex;
    bool hasDecoration;
    int decorationIndex;
};

// Function declarations
void loadTileSet(TileSet& tileSet, const std::string& filename, const std::vector<int>& validTiles);

#endif // TILESET_HPP