#pragma once
#include <SFML\Graphics.hpp>
#include "Ball.h"
class Block {
private:
	int blockwidth;
	int blockheight;
	float blockoutlinewidth;
	sf::Color color = sf::Color::Yellow;
	sf::RectangleShape rectangle;
public:
	Block(int widthin, int heightin);
	Block(int widthin, int heightin, float xpos, float ypos);

	bool ballinteract(Ball& ball);

	void drawblock(sf::RenderWindow& window);
	void setcolor(sf::Color newcolor);
};