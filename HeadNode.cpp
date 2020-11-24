#include "HeadNode.h"

using namespace sfSnake;


HeadNode::HeadNode(sf::Vector2f position, float rotation):position_(position),rotation_(rotation)
{
    texture_.loadFromFile("Picture/Head.PNG");
    texture_.setSmooth(true);
    sprite_.setOrigin(10,10);
    sprite_.setPosition(position_);
    sprite_.setTexture(texture_);
}

void HeadNode::render(sf::RenderWindow& window)
{
    window.draw(sprite_);
}

void HeadNode::setPosition(sf::Vector2f position)
{
    position_ = position;
    sprite_.setPosition(position_);
}

void HeadNode::setPosition(float x, float y)
{
    position_.x = x;
    position_.y = y;
    sprite_.setPosition(position_);
}

void HeadNode::setRotation(float arg)
{
    rotation_ = arg;
    sprite_.setRotation(rotation_);
}

sf::Vector2f HeadNode::getPosition() const
{
    return position_;
}

float HeadNode::getRotation() const
{
    return rotation_;
}

sf::FloatRect HeadNode::getBounds() const
{
    return sprite_.getGlobalBounds();
}

void HeadNode::move(float xOffset, float yOffset)
{
    position_.x += xOffset;
    position_.y += yOffset;
    sprite_.setPosition(position_);
}
