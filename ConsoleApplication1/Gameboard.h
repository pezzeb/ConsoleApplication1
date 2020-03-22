#pragma once
#include<vector>
#include "Block.h"
#include "Ball.h"
#include "playerbar.h"
#include <SFML\Graphics.hpp>

class Gameboard {
private:
	std::vector<Block> blocks;
	std::vector<Ball> balls;
	sf::RectangleShape boardframe;
	playerbar gameboardbar;
	bool activegame = true;
	double score = 0;
	int numberOfLivesConsumed = 0;
	sf::Font scorefont;
	sf::Text scoretext;
	int stateofgame;

	//THIS SHOULD BE WRITTEN BETTER
	int widthofboardinclaorund = 1000;
	int heighofboardinclaorund = 700;
	int boardaroundwidth = 10;
	int offsetboard = 20;

	void addball(float x, float y);
	void addblock(int widthin, int heightin, float xpos, float ypos);
	double bounceobjects();

public:
	Gameboard();
	void resetgameboard(sf::RenderWindow& window);
	void drawboard(sf::RenderWindow& window);
	double steptime();
	void movebar(double dx);
	void setbarposition(double xpos);
	void changegamestate() { (activegame) ? activegame = false : activegame = true; }
	bool getgetstate() { return activegame; }
	int getoffsetboard() { return offsetboard; }
	int getwidthofboard() { return widthofboardinclaorund; }
	bool isendgame();
	void changescore(double dscore);
	double getscore() {return score;}
	double getnumberOfLivesConsumed() { return numberOfLivesConsumed; }
	void incrementnumberOfLivesConsumed() { numberOfLivesConsumed +=1; }
	int getQstateofgame() { return stateofgame; }
	void setQstateofgame();
};