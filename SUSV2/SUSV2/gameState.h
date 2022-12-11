#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "gameMap.h"

using namespace sf;
using namespace std;

class gameState : public state
{
private:
	gameDataRef _data;
	Clock _clock;
	int _gameState;

	gameMap* _map;

public:
	gameState(gameDataRef data);
	~gameState();
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
};