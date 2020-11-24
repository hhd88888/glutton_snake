#include "Fruits.h"

using namespace sfNewSnake;

BlackFruit::BlackFruit(sf::Vector2f position) : sfSnake::Fruit(sf::Color::Black, 0, position) {}

BrownFruit::BrownFruit(sf::Vector2f position) : sfSnake::Fruit(sf::Color(128, 42, 42), 0, position) {}

RedFruit::RedFruit(sf::Vector2f position) : sfSnake::Fruit(sf::Color::Red, 3.f, position) {}

BlueFruit::BlueFruit(sf::Vector2f position) : sfSnake::Fruit(sf::Color::Blue, 2.f, position) {}

GreenFruit::GreenFruit(sf::Vector2f position) : sfSnake::Fruit(sf::Color::Green, 1.f, position) {}
