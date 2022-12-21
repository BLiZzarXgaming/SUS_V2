#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "mainMenuState.h"
using namespace sf;
using namespace std;

//chaque state representera une vraie fenetre et herite de state, car on implementera
//un init, update, draw et handleInput different pour chaque fenetre.
class splashState : public state
{
private:
	gameDataRef _data;	//chaque state recevra le pointeur sur la gameData qui
	//donne acces au stateMachine, au RenderWindow, au
	//assertManager et au inputManager
	Clock _clock;		//1re fenetre a besoin d une clock car elle disparait
	//au bout de quelques secondes
	Sprite _background; //le sprite pour la background
public:
	splashState(gameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
};