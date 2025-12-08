#pragma once

#include "Scene/Scene.hpp"

namespace MemoryCard{
    const int CARDS_COUNT_INITIAL = 12;
    const int CARDS_COUNT_PER_LEVEL = 4;

    const float CARD_PAIR_VISIBLE_COOLDOWN_DURATION = 0.5f; // seconds

    const sf::Color CARD_OUTLINE_COLOR(sf::Color::White);

    const std::vector<sf::Color> CARDS_COLORS = {
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color(255, 165, 0), // Orange
        sf::Color(128, 0, 128)  // Purple
    };

    const std::string CARD_TEXTURE_FILENAME = "Card.png";
}