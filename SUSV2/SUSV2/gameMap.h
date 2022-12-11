#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "matrice.hpp"
#include <fstream>
#include <string>

using namespace sf;

class gameMap
{
private:
	gameDataRef _data;
	vector<Sprite> _mapSpritesMur;
	vector<Sprite> _mapSpritesSol;

public:
	gameMap(gameDataRef data);
	void draw()const;
	//const vector<Sprite>& getWalls()const;
};