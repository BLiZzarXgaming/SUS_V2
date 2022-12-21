/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : bullet.h                                                                   */
/* Date        : 21 decembre 2022                                                           */
/* But         : une balle qui vole et se dessine                                           */
/********************************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"

class bullet
{
private:
	gameDataRef _data;
	sf::Vector2f _position;												// la position de depart
	sf::Sprite _sprite;													// le sprite du bullet

	bool _estTire;														// si il est tire
	double _vitesse;													// la vitesse
	double _distanceY;													// la distance en y
	double _distanceX;													// la distance en x

	// s'assure que le bullet soit délimité quand il est tiré 
	double _porteBalle;													// la distance maximale 
	double _maxX;														// la position x max									
	double _minX;														// la position x min
	double _maxY;														// la position y max
	double _minY;														// la position y min

public:
	bullet(gameDataRef data);											// construit le bullet
	~bullet();															// destructeur de bullet
	void draw() const;													// dessine le bullet dans la fenetre

	void stopVol();														// arrete le deplacement du bullet
	bool getEstTire() const;											// regarde si le bullet est en vol
	void tirer(sf::Vector2f positionDepart, sf::Vector2f positionVise);	// tire un bullet dans une direction
	sf::FloatRect getPosition() const;									// donne la position du bullet (rectangle)
	sf::Sprite getSprite() const;										// donne le sprite du bullet
	void update(float dtenSeconde);										// update la balle
	bool ennemiTouche(sf::FloatRect);									// regarde si il touche un sprite
	sf::Vector2f getVectPosition();										// donne la position en coordonne

	bool operator<(const sf::Vector2f&) const;							// surcharge operateur <
	bool operator>(const sf::Vector2i&) const;							// surcharge operateur >


};