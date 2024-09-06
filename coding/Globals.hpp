#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <utility>

// Константы
const int TILE_SIZE = 32;
const int TILE_COUNT_X = 4;
const int TILE_COUNT_Y = 4;
const int CHUNK_SIZE = 16;
const int EXPANSION_SIZE = 10;
const int PRELOAD_DISTANCE = 2;
const int INVENTORY_SIZE = 9;
const int global_water = 200;
const int minClusterSize = 2;
const int maxClusterSize = 10;

// Global variables
extern bool chatActive;
extern std::string chatInput;
extern std::vector<std::string> chatMessages;
extern sf::Color cursorColor;
extern sf::Clock cursorClock;
extern bool showCursor;
extern float cursorBlinkTime;
extern int cursorPosition;

extern sf::Clock staminaClock;
extern bool axeActive;

// Perlin noise parameters
extern const float SCALE;
extern const float WATER_THRESHOLD;
extern const float LAND_THRESHOLD;

// Base and detail scales for Perlin noise
extern const float BASE_SCALE;
extern const float DETAIL_SCALE;

extern std::vector<std::pair<int, int>> pos;

extern bool debugMode;

extern float currentStamina; 
extern const float maxStamina; 
extern const float runStaminaDrainRate; 
extern const float stepStaminaDrainRate; 
extern const float normalRecoveryRate; 
extern const float fastRecoveryRate; 

extern int scrollOffset;
extern int maxVisibleMessages;

extern const float chatHeight;

extern int heroChunkX;
extern int heroChunkY;

extern int woodCount;

#endif // GLOBALS_HPP