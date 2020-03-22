#pragma once
#include<vector>
#include <SFML\Graphics.hpp>
class Ball
{
private:
	std::vector<double> curpos{ 0,0 };
	std::vector<double> curvel{ 0,0 };
	std::vector<double> curacc{ 0,0 };
	std::vector<double> newpos{ 0,0 };
	std::vector<double> newvel{ 0,0 };
	std::vector<double> newacc{ 0,0 };
	float radius=10;
	sf::Color color = sf::Color::Blue;
	sf::CircleShape ballobj;
public:
	Ball(double xposin, double yposin);
	Ball(double xposin, double yposin, double xvelin, double yvelin);
	Ball(double xposin, double yposin, double xvelin, double yvelin, double xaccin, double yaccin);

	void steptime(double tt);
	std::vector<double> getpos();
	std::vector<double> getvel();
	std::vector<double> getacc();
	float getradius() { return radius; };

	void setpos(double x, double y);
	void setvel(double x, double y);
	void setacc(double x, double y);

	void bounceballx();
	void bouncebally();

	void drawball(sf::RenderWindow& window);

};