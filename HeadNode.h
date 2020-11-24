#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    class HeadNode
    {
    public:
        HeadNode(sf::Vector2f position = sf::Vector2f(0, 0),float rotation = 0.f);
        void render(sf::RenderWindow& window);

        void setPosition(sf::Vector2f position);
	    void setPosition(float x, float y);
        void setRotation(float arg);

        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        float getRotation() const;

        void move(float xOffset, float yOffset);

    private:
        sf::Sprite sprite_;
        sf::Texture texture_;

        sf::Vector2f position_;
        float rotation_;
    };
};