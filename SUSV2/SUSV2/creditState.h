/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : creditState.h                                                              */
/* Date        : 21 decembre 2022                                                           */
/* But         : afficher les credit et reveien au menu apres                               */
/********************************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "mainMenuState.h"
using namespace sf;

class creditState : public state
{
private:
	gameDataRef _data;	//chaque state recevra le pointeur sur la gameData qui
	//donne accès au stateMachine, au RenderWindow, au
	//assetManager et au inputManager
	Sprite _background; //le sprite pour la background

public:
	creditState(gameDataRef data);
	void init();				// initialise le state
	void handleInput();			// gere les entrees
	void update(float dt);		// update le state (pas utilise)
	void draw(float dt) const;	// dessine le state
};