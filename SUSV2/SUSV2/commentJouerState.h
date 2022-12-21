#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "mainMenuState.h"
using namespace sf;

class commentJouerState : public state
{
private:
	gameDataRef _data;	//chaque state recevra le pointeur sur la gameData qui
	//donne accès au stateMachine, au RenderWindow, au
	//assetManager et au inputManager
	Sprite _background; //le sprite pour la background

public:
	commentJouerState(gameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
};