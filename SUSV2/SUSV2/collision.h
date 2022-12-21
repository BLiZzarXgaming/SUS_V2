#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
using namespace sf;
class collision
{
public:
	bool checkSpriteCollision(Sprite sprite1, float scale1, Sprite sprite2, float scale2)const;
};