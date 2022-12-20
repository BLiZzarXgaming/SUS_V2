#include <SFML/Window.hpp>
using namespace sf;
#include "game.h"
#define SCREEN_WIDTH sf::VideoMode::getDesktopMode().width
#define SCREEN_HEIGHT sf::VideoMode::getDesktopMode().height
int main()
{
	game SUS(SCREEN_WIDTH, SCREEN_HEIGHT, "SUS: RELOADED");
	return EXIT_SUCCESS;
}