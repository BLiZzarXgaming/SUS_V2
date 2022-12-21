#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "player.h"
#include "bullet.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "state.hpp"
#include "gameMap.h"
#include "hud.h"
#include "boss.h"
#include "collision.h"
#include "fade.h"
#include "bossFightState.h"

using namespace sf;
using namespace std;
//chaque state repr�sentera une vraie fen�tre et h�rite de state, car on impl�mentera 
//un init, update, draw et handleInput diff�rent pour chaque fen�tre.

class gameState : public state
{
private:
	gameDataRef _data;

	Sprite _background;					//le sprite pour la background
	Sprite _trigger;
	player* _player;

	Clock _clock;

	int _gameState;

	sf::Vector2f _posSourisJeu;
	sf::View _viewJoueur;

	//Music _music;

	gameMap* _map;
	int _collidingWallID;

	Hud* _hud;

	fade* _fade;

	bullet* _balle;

	collision _collision;


public:
	gameState(gameDataRef data);
	~gameState();
	void init();
	void handleInput();
	void update(float dt);
	void initBossFight(float dt);
	void draw(float dt) const;
};