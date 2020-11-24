#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "Fruits.h"

using namespace sfSnake;

const int Snake::InitialSize = 4;

Direction::Direction(float x, float y, float arg) : x(x), y(y), arg(arg){};

Snake::Snake() : hitSelf_(false), direction_(Direction(0, -1, 0)),
                 head_(sf::Vector2f(Game::Width / 2, Game::Height / 2))
{
    initNodes();

    pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);

    dieBuffer_.loadFromFile("Sounds/die.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}

void Snake::initNodes()
{
    for (int i = 0; i < Snake::InitialSize; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(
            Game::Width / 2,
            Game::Height / 2 + (SnakeNode::Distance * (i + 1)))));
    }
}

void Snake::handleInput(sf::RenderWindow &window)
{
    HeadNode &headnode = head_;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        direction_.x = 0;
        direction_.y = -1;
        direction_.arg = 0.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        direction_.x = 0;
        direction_.y = 1;
        direction_.arg = 180.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction_.x = -1;
        direction_.y = 0;
        direction_.arg = 270.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction_.x = 1;
        direction_.y = 0;
        direction_.arg = 90.f;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mouse_pixel = sf::Mouse::getPosition(window);
        if (mouse_pixel.x < (int)window.getSize().x && mouse_pixel.x > 0 && mouse_pixel.y < (int)window.getSize().y && mouse_pixel.y > 0)
        {
            sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_pixel);
            sf::Vector2f head_position = headnode.getPosition();
            float distance = sqrt(pow(mouse_position.x - head_position.x, 2) + pow(mouse_position.y - head_position.y, 2));
            direction_.x = (mouse_position.x - head_position.x) / distance;
            direction_.y = (mouse_position.y - head_position.y) / distance;
            if (direction_.y >0)
            {
                direction_.arg = 180.0 - atan(direction_.x / direction_.y) * 180.0 / (atan(1) * 4);
            }
            else
            {
                direction_.arg = -atan(direction_.x / direction_.y) * 180.0 / (atan(1) * 4);
            }
        }
    }
}

void Snake::update(sf::Time delta)
{
    move();
    checkEdgeCollisions();
    checkSelfCollisions();
}

int Snake::checkFruitCollisions(std::vector<Fruit *> &fruits)
{
    decltype(fruits.begin()) toRemove = fruits.end();

    for (auto it = fruits.begin(); it != fruits.end(); ++it)
    {
        if ((*it)->getBounds().intersects(head_.getBounds()))
            toRemove = it;
    }
    if (toRemove != fruits.end())
    {
        pickupSound_.play();
        int score = (*toRemove)->getScore();
        grow(score);
        delete *toRemove;
        fruits.erase(toRemove);
        return score;
    }

    return -1;
}

void Snake::grow(int score)
{
    for (int i = 0; i < score; i++)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_.end()->getPosition().x,
                                                nodes_.end()->getPosition().y),
                                                nodes_.end()->getRotation()));
    }
}

bool Snake::checkFruitGenerate(Fruit *fruit)
{
    bool result = true;
    if (fruit->getBounds().intersects(head_.getBounds()))
    {
        result = false;
    }
    for (auto node : nodes_)
    {
        if (fruit->getBounds().intersects(node.getBounds()))
        {
            result = false;
            break;
        }
    }
    return result;
}

unsigned Snake::getSize() const
{
    return nodes_.size() + 1;
}

bool Snake::hitSelf() const
{
    return hitSelf_;
}

void Snake::checkSelfCollisions()
{
    //for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
    //{
        //if (head_.getBounds().intersects(nodes_[i].getBounds()))
        //{
            //dieSound_.play();
            //sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            //hitSelf_ = true;
            //break;
        //}
    //}
    auto iter = nodes_.begin();
    ++iter;
    while(iter != nodes_.end())
    {
        if (head_.getBounds().intersects((iter++)->getBounds()))
        {
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitSelf_ = true;
            break;
        }
    }
}

void Snake::checkEdgeCollisions()
{
    HeadNode &headNode = head_;

    if (headNode.getPosition().x <= 0)
        headNode.setPosition(Game::Width, headNode.getPosition().y);
    else if (headNode.getPosition().x > Game::Width)
        headNode.setPosition(0, headNode.getPosition().y);
    else if (headNode.getPosition().y <= 0)
        headNode.setPosition(headNode.getPosition().x, Game::Height);
    else if (headNode.getPosition().y > Game::Height)
        headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{

    //for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
    //{
        //nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
        //nodes_[i].setRotation(nodes_.at(i - 1).getRotation());
    //}
    //nodes_[0].setPosition(head_.getPosition());
    //nodes_[0].setRotation(head_.getRotation());
    //head_.move(direction_.x * SnakeNode::Distance, direction_.y * SnakeNode::Distance);
    //head_.setRotation(direction_.arg);

    SnakeNode new_node;

    new_node.setPosition(head_.getPosition());
    new_node.setRotation(head_.getRotation());
    nodes_.insert(nodes_.begin(),new_node);
    nodes_.pop_back();
    head_.move(direction_.x * SnakeNode::Distance, direction_.y * SnakeNode::Distance);
    head_.setRotation(direction_.arg);
}

void Snake::render(sf::RenderWindow &window)
{
    for (auto node : nodes_)
        node.render(window);
    head_.render(window);
}