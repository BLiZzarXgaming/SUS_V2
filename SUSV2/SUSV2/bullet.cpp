/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : bullet.cpp                                                                 */
/* Date        : 21 decembre 2022                                                           */
/* But         : une balle qui vole et se dessine                                           */
/********************************************************************************************/
#include "bullet.h"

using namespace sf;

// construit le bullet
bullet::bullet(gameDataRef data) : _data(data)
{
	// les stats du bullet
	_vitesse = SPEED_BULLET;
	_porteBalle = RANGE_BULLET;
	_estTire = false;
	_distanceX = 0;
	_distanceY = 0;

	// pour l'image
	_data->assets.loadTexture("image balle", BULLET_FILEPATH);
	_sprite.setTexture(_data->assets.getTexture("image balle"));
}

// destructeur du bullet
bullet::~bullet()
{
	_vitesse = 0;
	_porteBalle = 0;
	_estTire = false;
	_distanceX = 0;
	_distanceY = 0;
}

// dessine le bullet
void bullet::draw() const
{
	_data->window.draw(_sprite);
}

// arrete le deplacement du bullet
void bullet::stopVol()
{
	_estTire = false;
}

// regarde si le bullet est en vol
bool bullet::getEstTire() const
{
	return _estTire;
}

// tire un bullet dans une direction
void bullet::tirer(sf::Vector2f positionDepart, sf::Vector2f positionVise)
{

	_estTire = true; // rend la balle tire

	_position.x = positionDepart.x;
	_position.y = positionDepart.y;

	// le gradient
	float gradient = (positionDepart.x - positionVise.x) / (positionDepart.y - positionVise.y);


	if (gradient < 0)
	{
		gradient *= -1;
	}

	// Calcule le ratio entre x et y
	float ratioXY = _vitesse / (1 + gradient);

	// Set la vitesse horizontal et vertical
	_distanceY = ratioXY;
	_distanceX = ratioXY * gradient;

	// oriente le bullet vers la bonne direction
	if (positionVise.x < positionDepart.x)
	{
		_distanceX *= -1;
	}

	if (positionVise.y < positionDepart.y)
	{
		_distanceY *= -1;
	}

	_minX = positionDepart.x - _porteBalle;
	_maxX = positionDepart.x + _porteBalle;
	_minY = positionDepart.y - _porteBalle;
	_maxY = positionDepart.y + _porteBalle;

	_sprite.setPosition(_position);
}

// donne la position du bullet (rectangle)
sf::FloatRect bullet::getPosition() const
{
	return _sprite.getGlobalBounds();
}

// donne le sprite du bullet
sf::Sprite bullet::getSprite() const
{
	return _sprite;
}

// update la balle
void bullet::update(float dtenSeconde)
{
	// update la position de la balle
	_position.x += _distanceX * dtenSeconde;
	_position.y += _distanceY * dtenSeconde;

	_sprite.setPosition(_position);

	// si trop loin
	if (_position.x < _minX || _position.x > _maxX ||
		_position.y < _minY || _position.y > _maxY)
	{
		_estTire = false;
	}
}

// regarde si il touche un sprite
bool bullet::ennemiTouche(sf::FloatRect ennemi)
{
	if (getPosition().intersects(ennemi)) {
		return true;
	}
	else
	{
		return false;
	}
}

// donne la position en coordonne
sf::Vector2f bullet::getVectPosition()
{
	return _position;
}

// surcharge operateur <
bool bullet::operator<(const sf::Vector2f& pos2) const
{
	return _position.x < pos2.x || _position.y < pos2.y;
}

// surcharge operateur >
bool bullet::operator>(const sf::Vector2i& pos2) const
{
	return _position.x > pos2.x || _position.y > pos2.y;
}