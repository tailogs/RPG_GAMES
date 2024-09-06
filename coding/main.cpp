#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib> // For std::rand and std::srand
#include <ctime>   // For std::time
#include <unordered_map>
#include <utility> // For std::pair
#include <functional> // For std::hash
#include <string> // For std::to_string
#include <queue>   // Для очереди
#include "my_resource.hpp"
#include "my_string.hpp"
#include "my_time.hpp"
#include "PerlinNoise.hpp"
#include "Player.hpp"
#include "MyCamera.hpp"
#include "Chunk.hpp"
#include "Debug.hpp"
#include "Globals.hpp"
#include "TileSet.hpp"
#include "DecorationSet.hpp"
#include "Inventory.hpp"
#include "Chunk.hpp"

Player player("player.png");
MyCamera my_camera(1920, 1080);
Debug debug;

bool g = true;
int x_ = 0, y_ = 0, i = 0;

// Функция для проверки состояния клавиш
bool isKeyPressed(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

void bubbleSort(int list[], int listLength) {
    while(listLength--) {
        bool swapped = false;
        for(int i = 0; i < listLength; i++) {
            if(list[i] > list[i + 1]) {
                std::swap(list[i], list[i + 1]);
                swapped = true;
            }
        }
        if(swapped == false) break;
	}
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализация генератора случайных чисел

    // Создание окна
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG_GAMES", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::RectangleShape staminaBar(sf::Vector2f(200, 20)); // Размер полосы выносливости
    staminaBar.setFillColor(sf::Color::Green); // Цвет полосы выносливости
    staminaBar.setOutlineColor(sf::Color::Black); // Цвет обводки
    staminaBar.setOutlineThickness(2); // Толщина обводки

    sf::RectangleShape staminaBarBackground(sf::Vector2f(200, 20)); // Фон полосы
    staminaBarBackground.setFillColor(sf::Color::Red); // Цвет фона
    staminaBarBackground.setOutlineColor(sf::Color::Black); // Цвет обводки
    staminaBarBackground.setOutlineThickness(2); // Толщина обводки

    // Загрузка текстур и спрайтов
    TileSet waterTileSet, earthTileSet, treeTileSet, sandTileSet;
    DecorationSet treeDecorationSet, cactusDecorationSet, flowersDecorationSet, grassDecorationSet, dryBushDecorationSet; // Объявляем переменную для декораций

    // Загрузка тайлсетов
    loadTileSet(waterTileSet, "tileset-water.png", {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    loadTileSet(earthTileSet, "tileset-earth.png", {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    loadTileSet(sandTileSet, "tileset-sand.png", {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    loadDecorationSet(treeDecorationSet, "tileset-tree.png"); // Загрузка декораций
    loadDecorationSet(cactusDecorationSet, "tileset-cactus.png"); // Загрузка декораций
    loadDecorationSet(flowersDecorationSet, "tileset-flowers.png"); // Загрузка декораций
    loadDecorationSet(grassDecorationSet, "tileset-grass.png"); // Загрузка декораций
    loadDecorationSet(dryBushDecorationSet, "tileset-dry-bush.png"); // Загрузка декораций

    // Загрузка текстуры топора
    sf::Texture axeTexture;
    if (!axeTexture.loadFromFile(getResource("axe.png", "img")))
    {
        std::cerr << "Ошибка загрузки axe.png" << std::endl;
        return -1;
    }
    sf::Sprite axeSprite(axeTexture);
    
    // Загрузка текстуры дебага
    sf::Texture debugTexture;
    if (!debugTexture.loadFromFile(getResource("DEBUG.png", "img")))
    {
        std::cerr << "Ошибка загрузки DEBUG.png" << std::endl;
        return -1;
    }
    sf::Sprite debugSprite(debugTexture);

    // Загрузка текстуры топора
    sf::Texture treeTexture;
    if (!treeTexture.loadFromFile(getResource("tree.png", "img")))
    {
        std::cerr << "Ошибка загрузки tree.png" << std::endl;
        return -1;
    }
    sf::Sprite treeSprite(treeTexture);

    // Загрузка текстуры дров
    sf::Texture firewoodTexture;
    if (!firewoodTexture.loadFromFile(getResource("firewood.png", "img")))
    {
        std::cerr << "Ошибка загрузки firewood.png" << std::endl;
        return -1;
    }
    sf::Sprite firewoodSprite(firewoodTexture);

    // Карта чанков
    std::unordered_map<std::pair<int, int>, Chunk, pair_hash> chunks;

    // Создание камеры
    sf::View camera(sf::FloatRect(0, 0, 1920, 1080));
    camera.setSize(1920, 1080); // Установить размер камеры равным размеру окна

    // Инвентарь
    std::vector<InventoryItem> inventory(INVENTORY_SIZE);
    inventory[0].sprite = axeSprite; // Добавление топора в инвентарь
    inventory[0].quantity = 1;

    for (auto& item : inventory)
    {
        item.active = false; // Изначально все предметы неактивны
    }

    // Установка шрифта для текста
    sf::Font font;
    if (!font.loadFromFile(getResource("arial.ttf", "fonts")))
    {
        std::cerr << "Ошибка загрузки arial.ttf" << std::endl;
        return -1;
    }

    // Создание текстового объекта для отображения выносливости
    sf::Text staminaText;
    staminaText.setFont(font);
    staminaText.setCharacterSize(14);
    staminaText.setFillColor(sf::Color::Black);
    staminaText.setPosition(25, 21); // Позиция текста выносливости на экран

    sf::Text chatText;
    chatText.setFont(font);
    chatText.setCharacterSize(20);
    chatText.setFillColor(sf::Color::White);

    // Создание вида для инвентаря
    sf::View inventoryView(sf::FloatRect(0, 0, 1920, 1080));
    const float inventoryOffsetY = window.getSize().y + 35; // Позиция инвентаря по вертикали (отступ от нижнего края)
    inventoryView.setCenter(window.getSize().x / 2.0f, inventoryOffsetY - 470); // Позиционирование вида инвентаря по центру по горизонтали

    // Основной игровой цикл
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R) { // Клавиша R
                    if (inventory[0].active) {
                        for (int dy = -PRELOAD_DISTANCE; dy <= PRELOAD_DISTANCE; ++dy) {
                            for (int dx = -PRELOAD_DISTANCE; dx <= PRELOAD_DISTANCE; ++dx) {
                                int chunkX = heroChunkX + dx;
                                int chunkY = heroChunkY + dy;
                                std::pair<int, int> chunkPos = {chunkX, chunkY};

                                if (chunks.find(chunkPos) != chunks.end()) {
                                    Chunk& chunk = chunks[chunkPos];

                                    for (auto it = chunk.treeDecorations.begin(); it != chunk.treeDecorations.end(); ) {
                                        float distance = std::sqrt(std::pow(it->x - player.getPositionX(), 2) + std::pow(it->y - player.getPositionY(), 2));

                                        if (distance <= 32.0f) {
                                            woodCount++; // Увеличиваем количество древесины
                                            std::cout << "Wood count: " << woodCount << std::endl; // Вывод для отладки

                                            const float epsilon = 0.1f; // Допускное значение
                                            std::cout << "Attempting to remove tree at position: (" << it->x << ", " << it->y << ")" << std::endl;

                                            // Удаление дерева из вектора деревьев
                                            it = chunk.treeDecorations.erase(it);
                                        } else {
                                            ++it;
                                        }
                                    }

                                    for (int y = 0; y < CHUNK_SIZE; ++y) {
                                        for (int x = 0; x < CHUNK_SIZE; ++x) {
                                            Tile& tile = chunk.tiles[y][x];

                                            if (tile.type == 0) { // Если это земля
                                                int posX = (chunkX * CHUNK_SIZE + x) * TILE_SIZE;
                                                int posY = (chunkY * CHUNK_SIZE + y) * TILE_SIZE;
                                                sf::FloatRect tileRect(posX, posY, TILE_SIZE, TILE_SIZE);

                                                if (tileRect.contains(player.getPositionX(), player.getPositionY())) {
                                                    // Очищаем спрайт декорации
                                                    chunk.decorations[y][x] = sf::Sprite(); // Устанавливаем пустой спрайт

                                                    std::cout << "Sprite at (" << x << ", " << y << ") removed.\n";
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::F3)
                {
                    debugMode = !debugMode;
                }

                if (event.key.code == sf::Keyboard::V)
                {
                    g = !g;
                }

                // Открытие чата
                if (event.key.code == sf::Keyboard::T && !chatActive)
                {
                    chatActive = true; // Открываем чат
                    chatInput.clear();  // Очистка ввода при активации чата
                    cursorPosition = 0;  // Начало строки
                }

                if (event.key.code == sf::Keyboard::Escape && chatActive)
                {
                    chatActive = false;
                }

                if (event.key.code == sf::Keyboard::Delete && chatActive)
                {
                    if (cursorPosition < chatInput.size())
                    {
                        chatInput.erase(cursorPosition, 1);
                    }
                }

                if (event.key.code == sf::Keyboard::Enter && chatActive)
                {
                    // Если чат активен и нажата клавиша Enter, отправляем сообщение
                    if (!chatInput.empty()) {
                        if (chatInput == "/debug") {
                            debugMode = !debugMode; // Переключаем режим отладки
                            chatMessages.push_back("|    (SYSTEM Done | Time: " + getCurrentTime() + "): Done command -> /debug" + std::string(debugMode ? "<START DEBUG>" : "<STOP DEBUG>"));
                        } else if (chatInput == "/exit") {
                            exit(0);
                        } else if (chatInput[0] == '/') {
                            chatMessages.push_back("|    (SYSTEM Error | Time: " + getCurrentTime() + "): Error -> Unknown command " + chatInput);
                        } else {
                            chatMessages.push_back("|    (USER SMS | Time: " + getCurrentTime() + "): " + chatInput);
                        }

                        if (chatMessages.size() > maxVisibleMessages) { // Ограничиваем количество сообщений до 5
                            chatMessages.erase(chatMessages.begin()); // Удаляем самое старое сообщение
                        }
                        chatInput.clear();
                        cursorPosition = 0; // Сбрасываем позицию каретки
                    }
                }

               if (chatActive)
                {
                    if (event.key.code == sf::Keyboard::Left && cursorPosition > 0)
                    {
                        cursorPosition--;
                    }
                    else if (event.key.code == sf::Keyboard::Right && cursorPosition < chatInput.size())
                    {
                        cursorPosition++;
                    }
                    else if (event.key.code == sf::Keyboard::Delete && cursorPosition < chatInput.size())
                    {
                        chatInput.erase(cursorPosition, 1);
                    }
                    else if (event.key.code == sf::Keyboard::Up)
                    {
                        if (scrollOffset < chatMessages.size() - maxVisibleMessages)
                        {
                            scrollOffset++;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        if (scrollOffset > 0)
                        {
                            scrollOffset--;
                        }
                    }
                }
            }

            if (chatActive && event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') // Обработка удаления символов
                {
                    if (cursorPosition > 0)
                    {
                        chatInput.erase(cursorPosition - 1, 1);
                        cursorPosition--;  // Перемещаем каретку назад
                    }
                }
                else if (event.text.unicode == '\r') // Обработка Enter (отправка сообщения)
                {
                    if (!chatInput.empty())
                    {
                        std::string message = "INPUT > " + chatInput + " [" + getCurrentTime() + "]";
                        chatMessages.push_back(message);
                        chatInput.clear(); // Очистка ввода после отправки
                    }
                }
                else if (event.text.unicode < 128)
                {
                    chatInput.insert(cursorPosition, 1, static_cast<char>(event.text.unicode));
                    cursorPosition++;  // Перемещаем каретку вперед
                }
            }

            if (chatActive && event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0) // Прокрутка вверх
                {
                    if (scrollOffset < chatMessages.size() - maxVisibleMessages)
                    {
                        scrollOffset++;
                    }
                }
                else if (event.mouseWheelScroll.delta < 0) // Прокрутка вниз
                {
                    if (scrollOffset > 0)
                    {
                        scrollOffset--;
                    }
                }
            }
        }

        // Обработка ввода для активации предметов инвентаря
        if (!chatActive) // Игнорируем управление, если чат активен
        {
            for (int i = 0; i < INVENTORY_SIZE; ++i)
            {
                if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + i)))
                {
                    for (auto& item : inventory)
                    {
                        item.active = false; // Деактивировать все предметы
                    }
                    if (i < inventory.size())
                    {
                        inventory[i].active = true; // Активировать выбранный предмет
                    }
                    break;
                }
            }
        }

        // Управление героем и камерой
        sf::Vector2f movement(0, 0);
        
        // Определение текущей скорости движения
        float currentSpeed = player.getWalkSpeed();

        float deltaTime = staminaClock.restart().asSeconds(); // Время с последнего кадра

        bool isRunning = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift));
        bool isMoving = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        // Обновление стамины
        if (isRunning && !chatActive) {
            // Если игрок бегает
            currentSpeed = player.getRunSpeed();
            if (currentStamina > 0) {
                currentStamina -= runStaminaDrainRate * deltaTime;
                if (currentStamina < 0) currentStamina = 0; // Не даем уйти в отрицательные значения
            }
        } else if (isMoving && !chatActive) {
            // Если игрок движется, но не бегает
            currentSpeed = player.getWalkSpeed();
            if (currentStamina > 0) {
                currentStamina -= stepStaminaDrainRate * deltaTime;
                if (currentStamina < 0) currentStamina = 0; // Не даем уйти в отрицательные значения
            }
        } else {
            // Если игрок не движется
            currentSpeed = player.getWalkSpeed();
            if (currentStamina < maxStamina) {
                currentStamina += fastRecoveryRate * deltaTime;
                if (currentStamina > maxStamina) currentStamina = maxStamina; // Не даем превысить максимум
            }
        }
        
        if (!chatActive) // Игнорируем движение, если чат активен
        {
            // Двигаемся только если стамина больше 0
            if (currentStamina > 0) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= currentSpeed;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += currentSpeed;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= currentSpeed;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += currentSpeed;
            }
        }


        if (movement != sf::Vector2f(0, 0))
        {
            if (my_camera.getFollowHero())
            {
                player.setPositionVector(player.getPosition() + movement);
                camera.setCenter(player.getPositionX(), player.getPositionY());
            }
            else
            {
                my_camera.setFollowHero(true);
                camera.setCenter(player.getPositionX(), player.getPositionY());
            }
        }

        
        if (!chatActive) // Игнорируем движение, если чат активен
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                camera.move(0, -my_camera.getSpeed());
                my_camera.setFollowHero(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                camera.move(0, my_camera.getSpeed());
                my_camera.setFollowHero(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                camera.move(-my_camera.getSpeed(), 0);
                my_camera.setFollowHero(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                camera.move(my_camera.getSpeed(), 0);
                my_camera.setFollowHero(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                my_camera.setFollowHero(true);
                camera.setCenter(player.getPosition());
            }
        }

        // Определение текущего чанка героя
        heroChunkX = static_cast<int>(player.getPositionX() / (TILE_SIZE * CHUNK_SIZE));
        heroChunkY = static_cast<int>(player.getPositionY() / (TILE_SIZE * CHUNK_SIZE));

        // Загрузка или генерация чанков вокруг героя
        for (int dy = -PRELOAD_DISTANCE; dy <= PRELOAD_DISTANCE; ++dy)
        {
            for (int dx = -PRELOAD_DISTANCE; dx <= PRELOAD_DISTANCE; ++dx)
            {
                int chunkX = heroChunkX + dx;
                int chunkY = heroChunkY + dy;
                std::pair<int, int> chunkPos = {chunkX, chunkY};
                
                // Проверяем, есть ли уже созданный чанк
                auto it = chunks.find({chunkX, chunkY});

                if (it == chunks.end())
                {
                    Chunk chunk;
                    generateChunk(chunk, chunkX, chunkY, waterTileSet, earthTileSet, sandTileSet, treeDecorationSet, cactusDecorationSet, flowersDecorationSet, grassDecorationSet, dryBushDecorationSet);
                    chunks[chunkPos] = chunk;
                }
            }
        }

        window.clear();

        // Установка вида камеры
        window.setView(camera);

        // Отрисовка видимых чанков
        for (int dy = -PRELOAD_DISTANCE; dy <= PRELOAD_DISTANCE; ++dy) {
            for (int dx = -PRELOAD_DISTANCE; dx <= PRELOAD_DISTANCE; ++dx) {
                int chunkX = heroChunkX + dx;
                int chunkY = heroChunkY + dy;
                std::pair<int, int> chunkPos = {chunkX, chunkY};

                auto chunkIt = chunks.find(chunkPos);
                if (chunkIt != chunks.end()) {
                    const Chunk& chunk = chunkIt->second;
                    
                    for (int y = 0; y < CHUNK_SIZE; ++y) {
                        for (int x = 0; x < CHUNK_SIZE; ++x) {
                            const Tile& tile = chunk.tiles[y][x];
                            
                            // Выбор спрайта плитки в зависимости от типа
                            sf::Sprite tileSprite;
                            if (tile.type == 0) {
                                tileSprite = earthTileSet.sprites[tile.spriteIndex];
                            } else if (tile.type == 1) {
                                tileSprite = waterTileSet.sprites[tile.spriteIndex];
                            } else if (tile.type == 2 ) {
                                tileSprite = sandTileSet.sprites[tile.spriteIndex];
                            } else {
                                tileSprite = earthTileSet.sprites[tile.spriteIndex]; // Переходная плитка
                            }
                            
                            // Установка позиции и отрисовка плитки
                            tileSprite.setPosition((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE);
                            window.draw(tileSprite);

                            // Отрисовка декораций
                            const sf::Sprite& decoration = chunk.decorations[y][x];
                            if (decoration.getTexture() != nullptr) {
                                sf::Sprite decorationSprite = decoration;
                                decorationSprite.setPosition((chunkX * CHUNK_SIZE + x) * TILE_SIZE, (chunkY * CHUNK_SIZE + y) * TILE_SIZE);
                                if (g) 
                                    window.draw(decorationSprite);
                            }
                        }
                    }
                }
            }
        }

        // Отрисовка героя
        window.draw(player.getSprite());

        // Отрисовка линий от героя к деревьям, если режим отладки включен
        if (debugMode)
        {
            for (int dy = -PRELOAD_DISTANCE; dy <= PRELOAD_DISTANCE; ++dy)
            {
                for (int dx = -PRELOAD_DISTANCE; dx <= PRELOAD_DISTANCE; ++dx)
                {
                    int chunkX = heroChunkX + dx;
                    int chunkY = heroChunkY + dy;
                    std::pair<int, int> chunkPos = {chunkX, chunkY};

                    if (chunks.find(chunkPos) != chunks.end())
                    {
                        const Chunk& chunk = chunks[chunkPos];
                        debug.drawLineDecoration(window, chunk, player.getPosition(), font); // Передаем шрифт
                    }
                }
            }
        }

        // Установка вида для инвентаря
        window.setView(inventoryView);

        // Отрисовка слоя инструментов
        for (const auto& item : inventory)
        {
            if (item.quantity > 0)
            {
                window.draw(item.sprite);
            }
        }

        // Обновление курсора
        if (chatActive)
        {
            if (cursorClock.getElapsedTime().asSeconds() >= cursorBlinkTime)
            {
                showCursor = !showCursor;
                cursorClock.restart();
            }
        }

        // Плавное изменение цвета курсора
        sf::Time elapsed = cursorClock.getElapsedTime();
        float hue = (elapsed.asSeconds() * 0.5f); // Измените 0.5f на другую скорость изменения цвета
        cursorColor = sf::Color(255 * std::sin(hue), 255 * std::cos(hue), 255 * std::sin(hue));

        // Отрисовка слоя интерфейса (инвентарь)
        const float inventoryOffsetX = (window.getSize().x - INVENTORY_SIZE * 60) / 2.0f; // Центрирование инвентаря по горизонтали
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            sf::RectangleShape slot(sf::Vector2f(50, 50));
            if (inventory[i].active)
            {
                slot.setFillColor(sf::Color(0, 255, 0, 200)); // Зеленый цвет для активной ячейки
            }
            else
            {
                slot.setFillColor(sf::Color(100, 100, 100, 200)); // Обычный цвет для неактивной ячейки
            }
            
            // Устанавливаем обводку ячейки
            slot.setOutlineColor(sf::Color::Black); // Цвет обводки
            slot.setOutlineThickness(2); // Толщина обводки

            slot.setPosition(inventoryOffsetX + i * 60, inventoryOffsetY); // Позиционирование слота инвентаря
            window.draw(slot);

            // Отрисовка предмета в слоте инвентаря
            if (inventory[i].quantity > 0)
            {
                sf::Sprite itemSprite = inventory[i].sprite;
                itemSprite.setPosition(inventoryOffsetX + 5 + i * 60, inventoryOffsetY + 5); // Позиционирование предмета в слоте
                window.draw(itemSprite);

                // Отрисовка количества предметов
                sf::Text itemQuantityText;
                itemQuantityText.setFont(font);
                itemQuantityText.setString(std::to_string(inventory[i].quantity));
                itemQuantityText.setCharacterSize(14);
                itemQuantityText.setFillColor(sf::Color::White);
                itemQuantityText.setPosition(inventoryOffsetX + 5 + i * 60, inventoryOffsetY + 35); // Позиционирование текста количества
                window.draw(itemQuantityText);
            }
        }

        // В основном игровом цикле добавьте это после установки вида интерфейса:
        window.setView(window.getDefaultView()); // Переключаемся на вид по умолчанию (интерфейс)

        // Отрисовка интерфейса выносливости
        staminaBarBackground.setPosition(20, 20);
        staminaBar.setSize(sf::Vector2f(currentStamina * 2, 20)); // Ширина полосы выносливости пропорциональна значению текущей выносливости
        staminaBar.setPosition(20, 20);
        window.draw(staminaBarBackground);
        window.draw(staminaBar);

        // Отображение текущего уровня выносливости на экране
        staminaText.setString("Stamina: " + std::to_string(static_cast<int>(currentStamina)));
        window.draw(staminaText);

        // Отображение древесины в инвентаре
        sf::Text woodText;
        woodText.setFont(font);
        woodText.setCharacterSize(14);
        woodText.setFillColor(sf::Color::White);
        
        inventory[1].sprite = treeSprite; // Добавление топора в инвентарь
        inventory[1].quantity = woodCount;

        // Отрисовка чата
        if (chatActive)
        {
            // Фон чата
            sf::RectangleShape chatBackground(sf::Vector2f(window.getSize().x, chatHeight));
            chatBackground.setFillColor(sf::Color(0, 0, 0, 200));
            chatBackground.setPosition(0, window.getSize().y - chatHeight);
            window.draw(chatBackground);

            // Отображение текущего ввода с курсором
            std::string visibleChatInput = chatInput;
            if (showCursor) {
                visibleChatInput.insert(cursorPosition, "|"); // Вставляем курсор в строку на нужной позиции
            }
            chatText.setString("USER > " + visibleChatInput);
            chatText.setFillColor(cursorColor);
            chatText.setPosition(10, window.getSize().y - chatHeight + chatHeight - chatText.getCharacterSize() - 10); // Подкорректировано
            window.draw(chatText);

            // Отрисовка последних сообщений
            float yOffset = chatHeight - 80; // начальный отступ снизу от chatBackground
            int visibleMessagesCount = std::min(static_cast<int>(chatMessages.size()), maxVisibleMessages); // Убедиться, что не больше 5 сообщений видно

            for (auto it = chatMessages.rbegin(); it != chatMessages.rend() && visibleMessagesCount > 0; ++it, --visibleMessagesCount)
            {
                // Выбор цвета в зависимости от отправителя
                if (it->rfind("USER >", 0) == 0) {
                    chatText.setFillColor(sf::Color(255, 215, 0)); // USER > золотым цветом
                } else if (it->rfind("|    (SYSTEM Done | Time:", 0) == 0) {
                    chatText.setFillColor(sf::Color::Green); // Системные сообщения об успехе зелёным цветом
                } else if (it->rfind("|    (SYSTEM Error | Time:", 0) == 0) {
                    chatText.setFillColor(sf::Color::Red); // Системные сообщения об ошибке красным цветом
                } else if (it->rfind("|    AI >", 0) == 0) {
                    chatText.setFillColor(sf::Color::Blue); // AI > синим цветом
                } else {
                    chatText.setFillColor(sf::Color::White); // Другие сообщения белым цветом
                }

                chatText.setString(*it);
                chatText.setPosition(10, window.getSize().y - chatHeight + yOffset); // Подкорректировано
                window.draw(chatText);

                yOffset -= chatText.getCharacterSize() + 10; // Отступ между сообщениями увеличен до 5 пикселей
            }
        }

        // Отрисовка слоя текста (пока пусто)
        window.display();
    }

    return 0;
}