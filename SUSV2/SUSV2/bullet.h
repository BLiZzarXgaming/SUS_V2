#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include <list>
#include "game.h"

struct balleEtDir {
	Sprite balle;
	double distX;
	double distY;
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