#include "Chunk.hpp"
#include "PerlinNoise.hpp" // Include if you have a separate PerlinNoise file
#include <cstdlib> // For std::rand()

struct Chunk;
struct pair_hash;

// Function for generating a water cluster
void generateWaterCluster(Chunk& chunk, int startX, int startY) {
    int minClusterSize = 20;
    int maxClusterSize = 100;
    int clusterSize = minClusterSize + std::rand() % (maxClusterSize - minClusterSize + 1);
    std::queue<std::pair<int, int>> queue;
    queue.push({startX, startY});
    
    while (!queue.empty() && clusterSize > 0) {
        auto [x, y] = queue.front();
        queue.pop();
        
        if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_SIZE) continue;
        if (chunk.tiles[y][x].type == 1) continue;

        chunk.tiles[y][x].type = 1;
        --clusterSize;

        queue.push({x + 1, y});
        queue.push({x - 1, y});
        queue.push({x, y + 1});
        queue.push({x, y - 1});

        float sandProbability = 0.2f;
        std::vector<std::pair<int, int>> neighbors = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
        for (auto [nx, ny] : neighbors) {
            if (nx >= 0 && nx < CHUNK_SIZE && ny >= 0 && ny < CHUNK_SIZE && chunk.tiles[ny][nx].type == 0) {
                if (std::rand() / static_cast<float>(RAND_MAX) < sandProbability) {
                    chunk.tiles[ny][nx].type = 2;
                }
            }
        }
    }
}

// Function for generating a chunk
void generateChunk(Chunk& chunk, int chunkX, int chunkY, const TileSet& waterTileSet, const TileSet& earthTileSet, const TileSet& sandTileSet, const DecorationSet& treeDecorationSet, const DecorationSet& cactusDecorationSet, const DecorationSet& flowersDecorationSet, const DecorationSet& grassDecorationSet, const DecorationSet& dryBushDecorationSet) {
    chunk.tiles.resize(CHUNK_SIZE, std::vector<Tile>(CHUNK_SIZE));
    chunk.decorations.resize(CHUNK_SIZE, std::vector<sf::Sprite>(CHUNK_SIZE, sf::Sprite()));
    chunk.treeDecorations.clear();

    float biomeNoise = PerlinNoise::perlinNoise(chunkX * BASE_SCALE, chunkY * BASE_SCALE);

    const TileSet* groundTileSet;
    float treeProbability = 0.0f;
    float flowerProbability = 0.0f;
    float grassProbability = 0.0f;
    float cactusProbability = 0.0f;
    float dryBushProbability = 0.0f;
    float waterClusterProbability = 0.001f;
    float sandProbability = 0.0f; 

    if (biomeNoise < 0.70f) {
        groundTileSet = &earthTileSet;
        treeProbability = 0.15f;
        flowerProbability = 0.1f;
        grassProbability = 0.1f;
    } else if (biomeNoise < 0.90f) {
        groundTileSet = &sandTileSet;
        cactusProbability = 0.05f;
        dryBushProbability = 0.05f;
        sandProbability = 1.0f;
    } else {
        groundTileSet = &waterTileSet;
    }

    for (int y = 0; y < CHUNK_SIZE; ++y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            float nx = (chunkX * CHUNK_SIZE + x) * BASE_SCALE;
            float ny = (chunkY * CHUNK_SIZE + y) * BASE_SCALE;
            float noise = PerlinNoise::perlinNoise(nx, ny);

            Tile tile;
            if (std::rand() / static_cast<float>(RAND_MAX) < sandProbability) {
                tile.type = 2;
            } else {
                tile.type = 0;
            }

            if (tile.type == 0 && std::rand() / static_cast<float>(RAND_MAX) < waterClusterProbability) {
                generateWaterCluster(chunk, x, y);
            }
            
            tile.spriteIndex = std::rand() % groundTileSet->sprites.size();
            chunk.tiles[y][x] = tile;
        }
    }

    for (int y = 0; y < CHUNK_SIZE; ++y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            Tile& tile = chunk.tiles[y][x];
            
            if (tile.type == 0) {
                if (std::rand() / static_cast<float>(RAND_MAX) < treeProbability) {
                    int treeIndex = std::rand() % treeDecorationSet.sprites.size();
                    sf::Sprite treeSprite = treeDecorationSet.sprites[treeIndex];
                    treeSprite.setPosition((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE);
                    chunk.decorations[y][x] = treeSprite;
                    chunk.treeDecorations.push_back(sf::Vector2f((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE));
                } else if (std::rand() / static_cast<float>(RAND_MAX) < flowerProbability) {
                    int flowerIndex = std::rand() % flowersDecorationSet.sprites.size();
                    sf::Sprite flowerSprite = flowersDecorationSet.sprites[flowerIndex];
                    flowerSprite.setPosition((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE);
                    chunk.decorations[y][x] = flowerSprite;
                } else if (std::rand() / static_cast<float>(RAND_MAX) < grassProbability) {
                    int grassIndex = std::rand() % grassDecorationSet.sprites.size();
                    sf::Sprite grassSprite = grassDecorationSet.sprites[grassIndex];
                    grassSprite.setPosition((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE);
                    chunk.decorations[y][x] = grassSprite;
                }
            } else if (tile.type == 2) {
                if (std::rand() / static_cast<float>(RAND_MAX) < cactusProbability) {
                    int cactusIndex = std::rand() % cactusDecorationSet.sprites.size();
                    sf::Sprite cactusSprite = cactusDecorationSet.sprites[cactusIndex];
                    cactusSprite.setPosition((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE);
                    chunk.decorations[y][x] = cactusSprite;
                } else if (std::rand() / static_cast<float>(RAND_MAX) < dryBushProbability) {
                    int dryBushIndex = std::rand() % dryBushDecorationSet.sprites.size();
                    sf::Sprite dryBushSprite = dryBushDecorationSet.sprites[dryBushIndex];
                    dryBushSprite.setPosition((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE);
                    chunk.decorations[y][x] = dryBushSprite;
                }
            }
        }
    }
}

void removeTree(Chunk& chunk, int x, int y, const TileSet& treeTileSet) {
    // Удаление дерева из списка деревьев
    chunk.treeDecorations.erase(std::remove(chunk.treeDecorations.begin(), chunk.treeDecorations.end(), sf::Vector2f((x * TILE_SIZE), (y * TILE_SIZE))), chunk.treeDecorations.end());

    // Удаление декорации дерева из плитки
    chunk.decorations[y][x] = sf::Sprite(); // Устанавливаем пустой спрайт

    // Обновление типа плитки
    chunk.tiles[y][x].type = 0; // Например, устанавливаем плитку как пустую
}
