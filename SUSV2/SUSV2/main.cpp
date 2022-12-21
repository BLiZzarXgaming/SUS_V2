#include <SFML/Window.hpp>
#include "game.h"

#define SCREEN_WIDTH sf::VideoMode::getDesktopMode().width
#define SCREEN_HEIGHT sf::VideoMode::getDesktopMode().height
using namespace sf;

int main()
{
	game SUS(SCREEN_WIDTH, SCREEN_HEIGHT, "SUS: RELOADED");
	return EXIT_SUCCESS;
}