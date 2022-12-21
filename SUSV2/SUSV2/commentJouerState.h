/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : commentJouerState.h                                                        */
/* Date        : 21 decembre 2022                                                           */
/* But         : afficher comment jouer et revenir au menu apres                            */
/********************************************************************************************/
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
	commentJouerState(gameDataRef data);	// le constructeur
	void init();							// initialise le state
	void handleInput();						// gere les entrees
	void update(float dt);					// update le state (pas utilise)
	void draw(float dt) const;				// dessine le state dans la fenetre
};