#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Color color, int score, sf::Vector2f position = sf::Vector2f(0, 0));

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

    int getScore();

    virtual ~Fruit(){};

protected:
	sf::CircleShape shape_;

	static const float Radius;
    int score_;
};
}

#endif