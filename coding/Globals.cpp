#include "Globals.hpp"

// Initialize global variables
bool chatActive = false;
std::string chatInput;
std::vector<std::string> chatMessages;
sf::Color cursorColor = sf::Color::White;
sf::Clock cursorClock;
bool showCursor = true;
float cursorBlinkTime = 0.5f;
int cursorPosition = 0;

sf::Clock staminaClock;
bool axeActive = false;

const float SCALE = 0.1f;
const float WATER_THRESHOLD = 0.30f;
const float LAND_THRESHOLD = 0.70f;

const float BASE_SCALE = 0.2f;
const float DETAIL_SCALE = 0.1f;

std::vector<std::pair<int, int>> pos;

bool debugMode = false;

float currentStamina = 100.0f; // Начальное значение выносливости
const float maxStamina = 100.0f; // Максимальная выносливость
const float runStaminaDrainRate = 10.0f; // Расход выносливости при беге (единицы/сек)
const float stepStaminaDrainRate = 2.0f; // Расход выносливости при движении (единицы/сек)
const float normalRecoveryRate = 2.0f; // Восстановление выносливости при движении (единицы/сек)
const float fastRecoveryRate = normalRecoveryRate * 10.0f; // Восстановление выносливости при стоянии на месте

int scrollOffset = 0; // Смещение прокрутки
int maxVisibleMessages = 33; // Максимальное количество видимых сообщений

const float chatHeight = 1080.0f;

int heroChunkX = 0;
int heroChunkY = 0;

int woodCount = 0; // Количество древесины в инвентаре