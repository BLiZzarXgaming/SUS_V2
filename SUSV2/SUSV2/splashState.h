/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette														*/
/* Nom         : splashState.h                                                              */
/* Date        : 21 decembre 2022                                                           */
/* But         : affiche un state pour mettre la compagnie et passer au menu apres          */
/********************************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "mainMenuState.h"
using namespace sf;
using namespace std;

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
	splashState(gameDataRef data);	// constructeur 
	void init();					// initialise le state
	void handleInput();				// gere les entrees
	void update(float dt);			// update le state
	void draw(float dt) const;		// dessine le state 
};