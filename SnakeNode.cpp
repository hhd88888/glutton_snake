#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 5.f;
const float SnakeNode::Radius = 10.f;
const float SnakeNode::Distance = 20.f;

SnakeNode::SnakeNode(sf::Vector2f position, float rotation)
: position_(position),rotation_(rotation)
{
    shape_.setOrigin(sf::Vector2f(SnakeNode::Radius,SnakeNode::Radius));
    shape_.setPosition(position_);
	shape_.setFillColor(sf::Color::Yellow);
	shape_.setRadius(SnakeNode::Radius);
    shape_.setOutlineColor(sf::Color::Yellow);
    shape_.setOutlineThickness(-1);

    rectShape_.setOrigin(sf::Vector2f(SnakeNode::Width/2, SnakeNode::Height/2));
    rectShape_.setPosition(position_);
    rectShape_.setRotation(rotation);
    rectShape_.setFillColor(sf::Color::Black);
    rectShape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
    rectShape_.setOutlineColor(sf::Color::Black);
    rectShape_.setOutlineThickness(-1);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
    rectShape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
    rectShape_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
    rectShape_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
    window.draw(rectShape_);
}

void SnakeNode::setRotation(float arg)
{
    rotation_ = arg;
    rectShape_.setRotation(rotation_);
}

float SnakeNode::getRotation() const
{
    return rotation_;
}