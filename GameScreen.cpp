#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <experimental/random>
#include <cassert>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "Fruits.h"

using namespace sfSnake;
using namespace sfNewSnake;
const int GameScreen::fruitNum = 8;

sf::Vector2f generatePosition()
{
    static std::default_random_engine engine;
    static bool start = true;
    if (start)
    {
        engine.seed(time(NULL));
        start = false;
    }
    std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
    static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
    return sf::Vector2f(xDistribution(engine), yDistribution(engine));
}

GameScreen::GameScreen() : snake_(), zeroCount_(0), scoreCount_(0)
{
    std::experimental::reseed(time(NULL));
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
    snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
    for (auto i = fruit_.size(); i < fruitNum; ++i)
        generateFruit();

    snake_.update(delta);
    int score = snake_.checkFruitCollisions(fruit_);
    if (score == 0)
    {
        --zeroCount_;
    }
    else if (score != -1)
    {
        --scoreCount_;
    }

    if (snake_.hitSelf())
        Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow &window)
{
    snake_.render(window);

    for (auto fruit : fruit_)
        (*fruit).render(window);

}

void GameScreen::generateFruit()
{
    Fruit *p;
    int color;
    sf::Vector2f position;
    while (true)
    {
        position = generatePosition();
        if (zeroCount_ < fruitNum * 0.25)
        {
            color = std::experimental::randint(1, 2);
            switch (color)
            {
            case 1:
                p = new BlackFruit(position);
                break;
            case 2:
                p = new BrownFruit(position);
                break;
            }
            if (snake_.checkFruitGenerate(p) && checkFruit(p))
            {
                ++zeroCount_;;
                break;
            }
        }
        else if (scoreCount_ < fruitNum * 0.75)
        {
            color = std::experimental::randint(1, 3);
            switch (color)
            {
            case 1:
                p = new RedFruit(position);
                break;
            case 2:
                p = new GreenFruit(position);
                break;
            case 3:
                p = new BlueFruit(position);
                break;
            }
            if (snake_.checkFruitGenerate(p) && checkFruit(p))
            {
                ++scoreCount_;
                break;
            }

        }

        if (p)
        {
            delete p;
            p = 0;
        }
    }

    fruit_.push_back(p);
}

bool GameScreen::checkFruit(Fruit *fruit)
{
    for (auto fru:fruit_)
    {
        if (fruit->getBounds().intersects(fru->getBounds()))
        return false;
    }
    return true;
}
