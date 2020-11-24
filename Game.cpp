#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
    : window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake"), gridColorNum_(3),backColorNum_(0),gridColor_(sf::Color::White),backColor_(sf::Color::White), gridStatus_(false)
{
    bgMusic_.openFromFile("Music/bg_music.wav");
    bgMusic_.setLoop(true);
    bgMusic_.play();
    texture_.loadFromFile("grids/16x16.jpg");
    sprite_.setTexture(texture_);
    sprite_.scale(sf::Vector2f(680.f / 631.f, 480.f / 461.f));
}

void Game::handleInput()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {
        gridColorNum_ = (gridColorNum_ + 1) % 4;
        gridColor(gridColorNum_);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        backColorNum_ = (backColorNum_ + 1) % 3;
        backColor(backColorNum_);
    }

    Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
    Game::Screen->update(delta);
}

void Game::render()
{
    window_.clear(backColor_);
    if (gridStatus_)
    {
        window_.draw(sprite_);
    }
    Game::Screen->render(window_);
    window_.display();
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window_.isOpen())
    {
        sf::Time delta = clock.restart();
        timeSinceLastUpdate += delta;

        while (timeSinceLastUpdate > Game::TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            handleInput();
            update(TimePerFrame);
        }

        render();
    }
}

void Game::gridColor(int gridColornum)
{
    switch (gridColornum)
    {
    case 0:
        gridStatus_ = true;
        gridColor_ = sf::Color(255, 255, 255,128);
        break;
    case 1:
        gridColor_ = sf::Color(0, 0, 0,128);
        break;
    case 2:
        gridColor_ = sf::Color(128, 42, 42,128);
        break;
    case 3:
        gridStatus_ = false;
        break;
    default:
        break;
    }
    sprite_.setColor(gridColor_);
}

void Game::backColor(int backColorNum)
{
    switch (backColorNum)
    {
    case 0:
        backColor_ = sf::Color::White;
        break;
    case 1:
        backColor_ = sf::Color::Black;
        break;
    case 2:
        backColor_ = sf::Color(128, 42, 42);
        break;
    default:
        break;
    }
}
