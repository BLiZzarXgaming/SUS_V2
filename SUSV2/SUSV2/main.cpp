#include <SFML/Window.hpp>
using namespace sf;
#include "game.h"
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024
int main()
{
	game flappy(SCREEN_WIDTH, SCREEN_HEIGHT, "SUS: RELOADED");
	return EXIT_SUCCESS;
}