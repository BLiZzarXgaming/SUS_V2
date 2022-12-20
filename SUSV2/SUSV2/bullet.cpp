#include "Bullet.h"

using namespace sf;

bullet::bullet(gameDataRef data) : _data(data)
{
	//_sprite.setTexture(_data->assets.getTexture("bullet"));
	_vitesse = SPEED_BULLET;
	_porteBalle = RANGE_BULLET;
	_estTire = false;
	_distanceX = 0;
	_distanceY = 0;
}

bullet::~bullet()
{

}

void bullet::draw()
{
	_data->window.draw(_sprite);
}

void bullet::stopVol()
{
	_estTire = false;
}

bool bullet::getEstTire() const
{
	return _estTire;
}

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

sf::FloatRect bullet::getPosition() const
{
	return _sprite.getGlobalBounds();
}

sf::Sprite bullet::getSprite() const
{
	return _sprite;
}

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

sf::Vector2f bullet::getVectPosition()
{
	return _position;
}

bool bullet::operator<(const sf::Vector2f& pos2) const
{
	return _position.x < pos2.x || _position.y < pos2.y;
}

bool bullet::operator>(const sf::Vector2i& pos2) const
{
	return _position.x > pos2.x || _position.y > pos2.y;
}