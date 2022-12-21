/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : bullet.h                                                                   */
/* Date        : 21 decembre 2022                                                           */
/* But         : une balle qui vole et se dessine                                           */
/********************************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include <list>
#include "game.h"

struct balleEtDir {
	Sprite balle;
	double distX;
	double distY;
	bool live;
};

class bullet
{
private:
	gameDataRef _data;

	list<balleEtDir> _bulletSprites;
	
public:
	bullet(gameDataRef data);
	~bullet();
	void draw();
	void tirer(sf::Vector2f positionDepart, sf::Vector2f positionVise);
	void update(float dt);
	list<balleEtDir>& getBulletSprites();
};