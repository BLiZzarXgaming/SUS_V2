#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
using namespace sf;
class collision
{
public:
	bool checkSpriteCollision(Sprite sprite1, Sprite sprite2)const;
};