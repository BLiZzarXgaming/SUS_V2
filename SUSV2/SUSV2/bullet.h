#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"

class bullet
{
public:
	bullet(gameDataRef data);
	~bullet();
	void draw() const;
	void stopVol();
	bool getEstTire() const;
	void tirer(sf::Vector2f positionDepart, sf::Vector2f positionVise);
	sf::FloatRect getPosition() const;
	sf::Sprite getSprite() const;
	void update(float dtenSeconde);
	bool ennemiTouche(sf::FloatRect);
	sf::Vector2f getVectPosition();

	bool operator<(const sf::Vector2f&) const;
	bool operator>(const sf::Vector2i&) const;

private:
	gameDataRef _data;
	sf::Vector2f _position;
	sf::Sprite _sprite;
	bool _estTire;
	double _vitesse;
	double _distanceY;
	double _distanceX;

	// s'assure que le bullet soit délimité quand il est tiré 
	double _porteBalle;
	double _maxX;
	double _minX;
	double _maxY;
	double _minY;
};