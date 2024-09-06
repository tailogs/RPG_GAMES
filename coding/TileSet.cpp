#include "TileSet.hpp"
#include <iostream>

void loadTileSet(TileSet& tileSet, const std::string& filename, const std::vector<int>& validTiles) {
    if (!tileSet.texture.loadFromFile(getResource(filename, "img"))) {
        std::cerr << "Ошибка загрузки " << filename << std::endl;
        exit(-1);
    }

    tileSet.sprites.clear();
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; ++i) {
        if (validTiles[i] == 1) {
            int x = (i % TILE_COUNT_X) * TILE_SIZE;
            int y = (i / TILE_COUNT_X) * TILE_SIZE;
            sf::Sprite sprite;
            sprite.setTexture(tileSet.texture);
            sprite.setTextureRect(sf::IntRect(x, y, TILE_SIZE, TILE_SIZE));
            tileSet.sprites.push_back(sprite);
        }
    }
}