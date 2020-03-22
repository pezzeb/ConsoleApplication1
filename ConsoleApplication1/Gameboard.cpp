#include "Gameboard.h"
#include "playerbar.h"
#include<iostream>
#include<string>
//#include<math.h>

Gameboard::Gameboard() {
	boardframe = sf::RectangleShape(sf::Vector2f(widthofboardinclaorund -2* boardaroundwidth, heighofboardinclaorund -2* boardaroundwidth));
	gameboardbar = playerbar();
	boardframe.setOutlineColor(sf::Color::Green);
	boardframe.setFillColor(sf::Color::Transparent);
	boardframe.setOutlineThickness(boardaroundwidth);
	boardframe.setPosition(offsetboard, offsetboard);
	scorefont.loadFromFile("./fonts/arial.ttf");
}

void Gameboard::addball(float x, float y) {
	balls.emplace_back(x, y, 0.1, 0.1);
}

void Gameboard::addblock(int widthin, int heightin, float xpos, float ypos) {
	blocks.emplace_back(widthin, heightin, xpos, ypos);
}

void Gameboard::resetgameboard(sf::RenderWindow &window) {

	//TEXT OBJECTs
	scoretext.setFont(scorefont); // font is a sf::Font
	scoretext.setString("Score: 0");
	score = 0;
	numberOfLivesConsumed = 0;
	scoretext.setCharacterSize(24); // in pixels, not points!
	scoretext.setFillColor(sf::Color::Red);
	scoretext.setStyle(sf::Text::Bold | sf::Text::Underlined);
	scoretext.setPosition(1050, 50);

	if (not(balls.size() > 0)) {
		addball(400.0f, 400.0f);
	}
	else{
		balls.clear();
		addball(400.0f, 400.0f);
	}
	

	int NumberInLayer = 12;
	int NumberOfRows = 7;
	double SingleoutlineWidth = 5.0;
	double WidthOfBLock = (widthofboardinclaorund - 2.0*boardaroundwidth - 2.0*NumberInLayer*SingleoutlineWidth) / (1.0*NumberInLayer);	double HeightOfBlock = 40;

	int iter = 0;
	for (int i = 0; i < NumberInLayer; ++i) {
		for (int j = 0; j < NumberOfRows; ++j) {
			addblock(WidthOfBLock, HeightOfBlock, offsetboard + SingleoutlineWidth + i*(WidthOfBLock+2.0*SingleoutlineWidth), offsetboard + SingleoutlineWidth + j * (HeightOfBlock + 2.0 * SingleoutlineWidth));
			iter += 1;
		}
	}

}

void Gameboard::drawboard(sf::RenderWindow& window) {
	window.clear();
	for (auto it = begin(blocks); it != end(blocks); ++it) {
		it->drawblock(window);
	}
	for (auto it = begin(balls); it != end(balls); ++it) {
		it->drawball(window);
	}
	gameboardbar.drawplayerbar(window);
	window.draw(boardframe);

	window.draw(scoretext);

	//TEMP
	auto posar = balls[0].getpos();
	auto velar = balls[0].getvel();
	sf::Text ballposx; sf::Text ballposy; sf::Text ballvelx; sf::Text ballvely;
	ballposx.setFont(scorefont); ballposy.setFont(scorefont); ballvelx.setFont(scorefont); ballvely.setFont(scorefont);
	ballposx.setString("ballpos x: " + std::to_string(posar[0])); 
	ballposy.setString("ballpos y: " + std::to_string(posar[1]));
	ballvelx.setString("ballvel x: " + std::to_string(velar[0]));
	ballvely.setString("ballvel y: " + std::to_string(velar[1]));
	ballposx.setCharacterSize(24); ballposy.setCharacterSize(24); ballvelx.setCharacterSize(24); ballvely.setCharacterSize(24);
	ballposx.setFillColor(sf::Color::Red); ballposy.setFillColor(sf::Color::Red);	ballvelx.setFillColor(sf::Color::Red); ballvely.setFillColor(sf::Color::Red);
	ballposx.setPosition(1050, 150); 
	ballposy.setPosition(1050, 200);
	ballvelx.setPosition(1050, 250);
	ballvely.setPosition(1050, 300);
	window.draw(ballposx);
	window.draw(ballposy);
	window.draw(ballvelx);
	window.draw(ballvely);

	window.display();
}

double Gameboard::steptime() {
	double reward = bounceobjects();
	balls[0].steptime(4.1);
	setQstateofgame();
	return reward;
}

void Gameboard::movebar(double dx) {
	double xpos = gameboardbar.getPositionx();
	if (xpos + dx < offsetboard) {
		//nothing
	}
	else if(xpos + dx > 1000 - gameboardbar.getwidthofbar())
	{
		//nothing
	}
	else 
	{
		gameboardbar.moveposition(dx);
	}
}

void Gameboard::setbarposition(double newxpos) {
	gameboardbar.setposition(newxpos);
}

double Gameboard::bounceobjects() {
	auto pos = balls[0].getpos();
	auto vel = balls[0].getvel();
	float rr = balls[0].getradius();
	double scoretochange = 0.0;
	// Border Bounce
	if (pos[0] > 1.0 * widthofboardinclaorund - rr - 1.0*boardaroundwidth and vel[0]>0) {
		balls[0].bounceballx();
	}
	if (pos[0] - rr < 1.0 * boardaroundwidth and vel[0]<0) {
		balls[0].bounceballx();
	}
	if (pos[1] > 1.0 * heighofboardinclaorund - rr - 1.0 * boardaroundwidth) {
		balls[0].bouncebally();
		scoretochange = -900;
		changescore(-900.0);
		incrementnumberOfLivesConsumed();
	}
	else if(pos[1] < 1.0 * boardaroundwidth + rr){
		balls[0].bouncebally();
	}

	// bar Bounce
	if (gameboardbar.getPositionx() < pos[0] && 1.0*gameboardbar.getPositionx() + 1.0 * gameboardbar.getwidthofbar() > pos[0]) {
		if (pos[1] + 1.0 * rr > gameboardbar.getPositiony() + gameboardbar.getheightofbar() and 
			pos[1]  < gameboardbar.getPositiony() + gameboardbar.getheightofbar() and
			vel[1] > 0) {
			balls[0].bouncebally();
		}
	}

	// Block Bounce
	
	if (blocks.size() > 0)
	{	
		auto it = blocks.begin();
		while (it != blocks.end()) {
			bool out = it->ballinteract(balls[0]);
			if (out) 
			{
				it = blocks.erase(it);
				scoretochange += 10;
				changescore(10.0);
				//std::cout << "CURRENT SCORE: " << getscore() << "\n";
			}
			else
			{
				++it;
			}
		}
	}

	return scoretochange;
}

bool Gameboard::isendgame() {
	if (0 == blocks.size()) {
		return true;
	}
	else 
	{
		return false;
	}
}

void Gameboard::changescore(double dscore) {
	score += dscore;
	std::string stmp = std::to_string(score);
	std::string tmp = "Score: " + stmp;
	scoretext.setString(tmp);
}

void Gameboard::setQstateofgame() {
	std::vector<double>  posen = balls[0].getpos();
	auto tmp = posen[0];
	int tmpint = std::floor(tmp / 160.0);
	if (tmpint > 6){
		stateofgame = 6;
	} else {
		stateofgame = tmpint;
	}

}
