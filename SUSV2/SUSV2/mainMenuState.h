/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : mainMenuState.h                                                            */
/* Date        : 21 decembre 2022                                                           */
/* But         : Affiche un menu avec des bouttons pour changer de state                    */
/********************************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include <vector>
#include "gameState.h"
#include "commentJouerState.h"
#include "creditState.h"
#include "statsState.h"
using namespace sf;

class mainMenuState : public state
{
private:
	gameDataRef _data;	// chaque state recevra le pointeur sur la gameData qui
						// donne accès au stateMachine, au RenderWindow, au
						// assetManager et au inputManager
	Sprite _background; // le sprite pour la background
	Sprite _title;		// le sprite pour le titre
	Sprite _playButton; // le sprite pour le boutton play

	int _bouttonActuel;	// l'index du boutton selectionne

	std::vector<sf::RectangleShape> _boutton;	// les bouttons
	std::vector<sf::Text> _texts;				// les textes dans les bouttons

public:
	mainMenuState(gameDataRef data);	// le constructeur de menu principale
	void init();						// initialise le menu principale
	void handleInput();					// gere tout les inputs du menu
	void update(float dt);				// udpade les elements du menu
	void draw(float dt) const;			// dessine la fenetre

	void moveDown();					// bouge le boutton choisi de 1 en bas
	void moveUp();						// bouge le boutton choisi de 1 en haut

	int getBouttonChoisi();				// donne l'index du boutton choisi
	void setBoutton(sf::Vector2f position, std::string message);	// cree un boutton 
};