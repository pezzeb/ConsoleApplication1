#include "playerbar.h"
#include <SFML\Graphics.hpp>

playerbar::playerbar() {
	bar = sf::RectangleShape(sf::Vector2f(widthofbar, heighofbar));
	bar.setPosition(400, 600);
	bar.setFillColor(sf::Color::Red);
}

void playerbar::drawplayerbar(sf::RenderWindow& window) {
	window.draw(bar);
}

int  playerbar::getPositionx() {
	return bar.getPosition().x;
}

int  playerbar::getPositiony() {
	return bar.getPosition().y;
}

void playerbar::moveposition(double dx) {
	bar.setPosition(bar.getPosition().x + dx, bar.getPosition().y);
	//auto temp = bar.getPosition().x;
}
void playerbar::setposition(double newxpos) {
	bar.setPosition(newxpos, bar.getPosition().y);
}