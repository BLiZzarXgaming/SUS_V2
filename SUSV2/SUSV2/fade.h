#pragma once

#include "game.h"
class fade
{
private:
	gameDataRef _data;
	RectangleShape _shape;
	bool _flashOn;
public:
	fade(gameDataRef data);
	void show(float dt);
	void draw();
};