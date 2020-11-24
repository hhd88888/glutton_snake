#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0),float rotation = 0.f);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
    void setRotation(float arg);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
    float getRotation() const;

	static const float Width;
	static const float Height;
    static const float Radius;
    static const float Distance;

private:
	sf::CircleShape shape_;
    sf::RectangleShape rectShape_;
	sf::Vector2f position_;
    float rotation_;
};
}

#endif