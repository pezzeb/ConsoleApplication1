#include "Ball.h"

Ball::Ball(double xposin, double yposin) 
{ 
	curpos[0] = xposin; 
	curpos[1] = yposin; 
	ballobj = sf::CircleShape(radius);
	ballobj.setFillColor(color);
	ballobj.setOutlineColor(sf::Color::Black);
	ballobj.setOutlineThickness(2.0f);
	ballobj.setPosition(curpos[0], curpos[1]);
}

Ball::Ball(double xposin, double yposin, double xvelin, double yvelin)
{
	curpos[0] = xposin;
	curpos[1] = yposin;
	curvel[0] = xvelin;
	curvel[1] = yvelin;
	ballobj = sf::CircleShape(radius);
	ballobj.setFillColor(color);
	ballobj.setOutlineColor(sf::Color::Black);
	ballobj.setOutlineThickness(2.0f);
	ballobj.setPosition(curpos[0], curpos[1]);
}

Ball::Ball(double xposin, double yposin, double xvelin, double yvelin, double xaccin, double yaccin)
{
	curpos[0] = xposin;
	curpos[1] = yposin;
	curvel[0] = xvelin;
	curvel[1] = yvelin;
	curacc[0] = xaccin;
	curacc[1] = yaccin;
	ballobj = sf::CircleShape(radius);
	ballobj.setFillColor(color);
	ballobj.setOutlineColor(sf::Color::Black);
	ballobj.setOutlineThickness(2.0f);
	ballobj.setOrigin(xposin, yposin);
	ballobj.setPosition(curpos[0], curpos[1]);
}


void Ball::steptime(double tt) {
	
	curpos[0] = curpos[0] + curvel[0] * tt;
	curpos[1] = curpos[1] + curvel[1] * tt;

	if (curpos[0] < 0) {
		curpos[0] = -0.01;
	}


	curvel[0] = curvel[0] + curacc[0] * tt;
	curvel[1] = curvel[1] + curacc[1] * tt;
	ballobj.setPosition(curpos[0], curpos[1]);

}

std::vector<double> Ball::getpos() {
	return curpos;
}
std::vector<double> Ball::getvel() {
	return curvel;
}
std::vector<double> Ball::getacc() {
	return curacc;
}

void Ball::setpos(double x, double y) {
	curpos[0] = x;
	curpos[1] = y;
}
void Ball::setvel(double x, double y) {
	curvel[0] = x;
	curvel[1] = y;
}
void Ball::setacc(double x, double y) {
	curacc[0] = x;
	curacc[1] = y;
}

void Ball::drawball(sf::RenderWindow& window) {
	window.draw(ballobj);
}
void Ball::bounceballx() {
	curvel[0] = -curvel[0];
}
void Ball::bouncebally() {
	curvel[1] = -curvel[1];
}