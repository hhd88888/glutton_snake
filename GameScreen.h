#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "Fruits.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	Snake snake_;
	std::vector<Fruit*> fruit_;
    unsigned int zeroCount_;//brown and black;
    unsigned int scoreCount_;//other color;
    static const int fruitNum;
    void generateFruit();
    bool checkFruit(Fruit *fruit);

    //sf::Vector2f generateXY();
};
}

#endif