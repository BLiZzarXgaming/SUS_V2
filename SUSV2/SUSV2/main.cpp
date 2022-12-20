#include <SFML/Window.hpp>
using namespace sf;
#include "game.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
int main()
{
	game flappy(SCREEN_WIDTH, SCREEN_HEIGHT, "SUS: RELOADED");
	return EXIT_SUCCESS;
}