#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "TileSet.hpp"
#include "DecorationSet.hpp"
#include "Globals.hpp"
#include <vector>
#include <queue>
#include <SFML/System/Vector2.hpp>
#include "PerlinNoise.hpp" // Include if you have a separate PerlinNoise file
#include <cstdlib> // For std::rand()

// Структура для хранения информации о чанке
struct Chunk {
    std::vector<std::vector<Tile>> tiles;
    std::vector<std::vector<sf::Sprite>> decorations;
    std::vector<sf::Vector2f> treeDecorations;

    // Метод для получения количества деревьев
    int getTreeCount() const {
        return static_cast<int>(treeDecorations.size());
    }
};

// Custom hash function for std::pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2;
    }
};

// Function declarations
void generateWaterCluster(Chunk& chunk, int startX, int startY);
void generateChunk(Chunk& chunk, int chunkX, int chunkY, const TileSet& waterTileSet, const TileSet& earthTileSet, const TileSet& sandTileSet, const DecorationSet& treeDecorationSet, const DecorationSet& cactusDecorationSet, const DecorationSet& flowersDecorationSet, const DecorationSet& grassDecorationSet, const DecorationSet& dryBushDecorationSet);
void removeTree(Chunk& chunk, int x, int y, const TileSet& treeTileSet);

#endif // CHUNK_HPP

