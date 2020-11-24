#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <list>

#include "SnakeNode.h"
#include "Fruit.h"
#include "Fruits.h"
#include "HeadNode.h"

namespace sfSnake
{
    class Direction
    {
    public:
        Direction(float x,float y,float arg);
        float x, y, arg;
    };

    class Snake
    {
    public:
        Snake();

        void handleInput(sf::RenderWindow& window);
        void update(sf::Time delta);
        void render(sf::RenderWindow &window);

        int checkFruitCollisions(std::vector<Fruit*> &fruits);
        bool checkFruitGenerate(Fruit *fruit);

        bool hitSelf() const;

        unsigned getSize() const;

    private:
        void move();
        void grow(int score);
        void checkEdgeCollisions();
        void checkSelfCollisions();
        void initNodes();

        bool hitSelf_;

        sf::Vector2f position_;
        Direction direction_;

        sf::SoundBuffer pickupBuffer_;
        sf::Sound pickupSound_;

        sf::SoundBuffer dieBuffer_;
        sf::Sound dieSound_;

        //std::vector<SnakeNode> nodes_;
        std::list<SnakeNode> nodes_;
        HeadNode head_;

        static const int InitialSize;
    };
} // namespace sfSnake

#endif