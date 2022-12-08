#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "map.hpp"

using namespace sf;

class gameMap
{
private:
	gameDataRef _data;
	//vector<Sprite> _landSprites;

public:
	gameMap(gameDataRef data);
	void draw()const;
	const vector<Sprite>& getSprites()const;
};