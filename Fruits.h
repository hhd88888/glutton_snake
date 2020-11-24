#pragma once

#include <SFML/Graphics.hpp>
#include "Fruit.h"

namespace sfNewSnake
{
    class BlackFruit : public sfSnake::Fruit
    {
    public:
        BlackFruit(sf::Vector2f position = sf::Vector2f(0, 0));
    };

    class BrownFruit : public sfSnake::Fruit
    {
    public:
        BrownFruit(sf::Vector2f position = sf::Vector2f(0, 0));
    };

    class RedFruit : public sfSnake::Fruit
    {
    public:
        RedFruit(sf::Vector2f position = sf::Vector2f(0, 0));
    };

    class BlueFruit : public sfSnake::Fruit
    {
    public:
        BlueFruit(sf::Vector2f position = sf::Vector2f(0, 0));
    };

    class GreenFruit : public sfSnake::Fruit
    {
    public:
        GreenFruit(sf::Vector2f position = sf::Vector2f(0, 0));
    };
} // namespace sfNewSnake