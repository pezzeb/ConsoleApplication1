#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Block.h"
#include "Gameboard.h"
#include "aiplayer.h"

int main() {

std::cout << "Main Program Start\n";
sf::RenderWindow window(sf::VideoMode(1400, 750), "SFML TUTORIAL", sf::Style::Close | sf::Style::Resize);

Gameboard Game;
Game.resetgameboard(window);
Game.setQstateofgame();

aiplayer ain(0.1, 1, 0.1);
ain.setGreedy(false);

int aiplayermove;
double reward;
int Qstateofgame1;
int Qstateofgame2;
int iter = 0;

aiplayermove = 0;
int aiplayermove_prev = 0;
bool printwindowAI = false;

int HumanOrAI;
std::cout << "AI is 0 and Human is 1\n";
std::cin >> HumanOrAI;

while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt)) 
		{
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
		}
		if(Game.getgetstate() and not(Game.isendgame())){

			//Manual input
			if (HumanOrAI == 1) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
				{
					//Game.movebar(-1.0);
					Game.setbarposition(Game.getoffsetboard() + 0.0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
				{
					//Game.movebar(+1.0);getwidthofboard
					Game.setbarposition(Game.getoffsetboard() + 245);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
				{
					//Game.movebar(+1.0);
					Game.setbarposition(Game.getoffsetboard() + 490);
				}
				Game.steptime();
				Game.drawboard(window);
			}
			else{
				Qstateofgame1 = Game.getQstateofgame();

				aiplayermove = ain.epsilongreedymove(Qstateofgame1, ain.getEps(), ain.getGreedy());
				if (1 == aiplayermove)
				{
					Game.setbarposition(Game.getoffsetboard() + 0.0);
				}
				else if (2 == aiplayermove)
				{
					Game.setbarposition(Game.getoffsetboard() + 245);
				}
				else if (3 == aiplayermove)
				{
					Game.setbarposition(Game.getoffsetboard() + 490);
				}

				if (printwindowAI) {
					Game.drawboard(window);
				}

				reward = Game.steptime();

				if (aiplayermove_prev != aiplayermove) {//Minus for moving
					reward += -0.1;
				}
				aiplayermove_prev = aiplayermove;

				Qstateofgame2 = Game.getQstateofgame();
				ain.updateq(reward, Qstateofgame1, aiplayermove, Qstateofgame2);
			}
		}
		else
		{
			Game.drawboard(window);
		}

		if (Game.isendgame()) {
			std::cout << "ITER: " << iter 
				      << " and the Gamescore was: " << Game.getscore() 
				<< " and the number of lives required was: " << Game.getnumberOfLivesConsumed()
				<< std::endl;

			Game.resetgameboard(window);
			Game.setQstateofgame();

			if ((0 == iter % 100 and iter > 0)) {
				printwindowAI = true;
				ain.setGreedy(true);
				ain.setLearningRate(ain.getLearningRate() / 3);
				ain.setEps(ain.getEps() / 3);
				iter += 1;
			}
			else {
				printwindowAI = false;
				iter += 1;
			}

		}
	}
return 0;
}