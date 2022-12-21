#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "bullet.h"
#include "player.h"
#include "ennemi.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "state.hpp"
#include "gameMap.h"
#include "hud.h"
#include "boss.h"
#include "collision.h"

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
	boss* _boss;

	Clock _clock;

	int _gameState;

	sf::Vector2f _posSourisJeu;
	sf::View _viewJoueur;

	//Music _music;

	gameMap* _map;
	int _collidingWallID;

	Hud* _hud;


	bullet* _balle;

	collision _collision;

	std::vector<ennemi*> _ennemis;


public:
	gameState(gameDataRef data);
	~gameState();
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
};