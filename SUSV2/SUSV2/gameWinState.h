#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "gameState.h"
#include "mainMenuState.h"
#include <fstream>

using namespace sf;
using namespace std;
//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera
//un init, update, draw et handleInput différent pour chaque fenêtre.
class gameWinState : public state
{
private:
	gameDataRef _data; //chaque state recevra le pointeur sur la gameData qui
	//donne accès au stateMachine, au RenderWindow, au
	//assertManager et au inputManager


	Text _scoreText;
	RectangleShape _rectangle;
	int _score;
	
public:
	gameWinState(gameDataRef data, int score);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
};