/********************************************************************************************/
/* Auteur      : Xavier Caouette                                                            */
/* Nom         : hud.h   																	*/
/* Date        : 21 decembre 2022                                                           */
/* But         : Objet qui donne des informations sur la vie et le nombre de balle sur un   */
/*               ecran                                                                      */
/********************************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include "game.h"
#include "state.hpp"

class Hud {
private:
	gameDataRef _data;

	// Sprite
	sf::Sprite _spriteVie;	// l'image de la barre actuelle
	sf::IntRect _rectVie;	// le rectangle pour couper

	// Texte
	sf::Text _nbBalle;		// texte qui s'affiche

public:
	Hud(gameDataRef data);	// le constructeur
	void setBalle(int);		// modifie le string du text nbr de balle
	void updateVie(int);	// modifie la vie du joueur

	void setPosition(sf::Vector2f position);	// place la barre de vie et le nombre de balle dans la fenetre
	void draw() const;							// Dessine la barre de vie et le nombre de balle
};