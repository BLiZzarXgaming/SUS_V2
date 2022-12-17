#pragma once

#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "player.h"
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera 
//un init, update, draw et handleInput différent pour chaque fenêtre.
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