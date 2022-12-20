#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include <vector>
//#include "gameState.h"
#include "commentJouerState.h"
#include "creditState.h"
#include "statsState.h"
using namespace sf;

class mainMenuState : public state
{
private:
	gameDataRef _data;	//chaque state recevra le pointeur sur la gameData qui
	//donne accès au stateMachine, au RenderWindow, au
	//assetManager et au inputManager
	Sprite _background; //le sprite pour la background
	Sprite _title;		//le sprite pour le titre
	Sprite _playButton; //le sprite pour le boutton play

	int _bouttonActuel;
	std::vector<sf::RectangleShape> _boutton;
	std::vector<sf::Text> _texts;

public:
	mainMenuState(gameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
	void moveDown();
	void moveUp();
	int getBouttonChoisi();
	void setBoutton(sf::Vector2f position, std::string message);
};