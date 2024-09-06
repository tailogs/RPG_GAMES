#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <SFML/Graphics.hpp>

// Структура для элемента инвентаря
struct InventoryItem {
    sf::Sprite sprite;
    int quantity;
    bool active;
};

void addInventory(sf::Sprite&, int);

#endif // INVENTORY_HPP