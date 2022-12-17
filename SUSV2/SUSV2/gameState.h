#pragma once

#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "player.h"
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
//chaque state repr�sentera une vraie fen�tre et h�rite de state, car on impl�mentera 
//un init, update, draw et handleInput diff�rent pour chaque fen�tre.
class gameState : public state
{
private:
	gameDataRef _data;

	Sprite _background;					//le sprite pour la background
	player* _player;

	Clock _clock;

	int _gameState;

	sf::Vector2f _posSourisJeu;
	sf::View _viewJoueur;

	Music _music;

public:
	gameState(gameDataRef data);
	~gameState();
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
};