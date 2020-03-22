#include "Block.h"

Block::Block(int widthin, int heightin) {
	blockwidth = widthin;
	blockheight = heightin;
	blockoutlinewidth = 5.0f;
	rectangle = sf::RectangleShape(sf::Vector2f(blockwidth, blockheight));
	rectangle.setFillColor(color);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(blockoutlinewidth);
	rectangle.setOrigin(widthin / 2.0, heightin / 2.0);
}

Block::Block(int widthin, int heightin, float xpos, float ypos) {
	blockwidth = widthin;
	blockheight = heightin;
	blockoutlinewidth = 5.0f;
	rectangle = sf::RectangleShape(sf::Vector2f(blockwidth, blockheight));
	rectangle.setFillColor(color);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(blockoutlinewidth);
	//rectangle.setOrigin(2.5f + widthin / 2.0, 2.5f + heightin / 2.0); //offset is because of the outline
	rectangle.setPosition(xpos, ypos);
}

bool Block::ballinteract(Ball& ball) {
	auto rectposx = rectangle.getPosition().x;
	auto rectposy = rectangle.getPosition().y;
	auto rrr = ball.getradius();
	auto ballpos = ball.getpos();

	bool outbool = false;
	//down and up
	if (rectposx < ballpos[0] and rectposx + 1.0*blockwidth > ballpos[0])
	{
		//down
		if (rectposy + 1.0*blockheight + rrr > ballpos[1] and 
			rectposy  + rrr < ballpos[1]and 
			ball.getvel()[1] < 0) {
			ball.bouncebally();
			outbool = true;
		}
		//up
		if (rectposy - rrr < ballpos[1] and 
			rectposy + 1.0*blockheight - rrr > ballpos[1] and
			ball.getvel()[1] > 0) {
			ball.bouncebally();
			outbool = true;
		}
	}

	//Right and Left
	if (rectposy - 1.0*blockoutlinewidth < ballpos[1] and ballpos[1] < rectposy + 1.0*blockoutlinewidth + 1.0 * blockheight)
	{	
		//Right
		if (rectposx + 1.0*blockoutlinewidth + blockwidth + rrr > ballpos[0] and 
			ballpos[0] > rectposx + blockwidth*0.5 + rrr //Litefullösning
			and ball.getvel()[0] < 0) {
			ball.bounceballx();
			outbool = true;
		}
		//Left
		if (rectposx - 1.0*blockoutlinewidth - 1.0*rrr < ballpos[0] and
			ballpos[0] < rectposx + +blockwidth * 0.5
			and ball.getvel()[0] > 0) {
			ball.bounceballx();
			outbool = true;
		}
	}

	return outbool;
}

void Block::drawblock(sf::RenderWindow& window) {
	window.draw(rectangle);
}

void Block::setcolor(sf::Color newcolor) {
	rectangle.setFillColor(newcolor);
}