#ifndef DECORATIONSET_HPP
#define DECORATIONSET_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Globals.hpp"
#include "my_resource.hpp"

// Структура для спрайтов декораций
struct DecorationSet {
    sf::Texture texture;
    std::vector<sf::Sprite> sprites;
};

// Function declarations
void loadDecorationSet(DecorationSet&, const std::string&);

#endif // DECORATIONSET_HPP