#pragma once
#include<vector>
#include <SFML\Graphics.hpp>
class playerbar
{
private:
	int heighofbar = 10;
	int widthofbar = 490;
	sf::RectangleShape bar;
public:

	playerbar();
	void drawplayerbar(sf::RenderWindow& window);
	void moveposition(double dx);
	void setposition(double dx);
	int getwidthofbar() { return widthofbar; }
	int getheightofbar() { return heighofbar; }
	int getPositionx();
	int getPositiony();
};