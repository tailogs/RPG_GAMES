#include "DecorationSet.hpp"

void loadDecorationSet(DecorationSet& decorationSet, const std::string& filename) {
    if (!decorationSet.texture.loadFromFile(getResource(filename, "img"))) {
        std::cerr << "Ошибка загрузки " << filename << std::endl;
        exit(-1);
    }

    decorationSet.sprites.clear();
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; ++i) {
        int x = (i % TILE_COUNT_X) * TILE_SIZE;
        int y = (i / TILE_COUNT_X) * TILE_SIZE;
        sf::Sprite sprite;
        sprite.setTexture(decorationSet.texture);
        sprite.setTextureRect(sf::IntRect(x, y, TILE_SIZE, TILE_SIZE));
        decorationSet.sprites.push_back(sprite);
    }
}