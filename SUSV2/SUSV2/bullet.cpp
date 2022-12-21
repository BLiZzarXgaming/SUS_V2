#include "bullet.h"

using namespace sf;

bullet::bullet(gameDataRef data) : _data(data)
{
}

bullet::~bullet()
{
}

void bullet::draw()
{
	for (list<balleEtDir>::iterator it = _bulletSprites.begin(); it != _bulletSprites.end(); it++)
		_data->window.draw(it->balle);
}

void bullet::tirer(sf::Vector2f positionDepart, sf::Vector2f positionVise)
{
	balleEtDir bulletTemp;
	Vector2f pos;

	bulletTemp.balle.setTexture(_data->assets.getTexture("bullet"));

	pos.x = positionDepart.x;
	pos.y = positionDepart.y;

	// le gradient
	float gradient = (positionDepart.x - positionVise.x) / (positionDepart.y - positionVise.y);

	if (gradient < 0)
	{
		gradient *= -1;
	}

	// Calcule le ratio entre x et y
	float ratioXY = 600 / (1 + gradient);

	// Set la vitesse horizontal et vertical
	bulletTemp.distY = ratioXY;
	bulletTemp.distX = ratioXY * gradient;

	// oriente le bullet vers la bonne direction
	if (positionVise.x < positionDepart.x)
		bulletTemp.distX *= -1;

	if (positionVise.y < positionDepart.y)
		bulletTemp.distY *= -1;

	bulletTemp.balle.setPosition(pos);
	_bulletSprites.push_back(bulletTemp);
}

list<balleEtDir>& bullet::getBulletSprites()
{
	return _bulletSprites;
}

void bullet::update(float dt)
{
	list<balleEtDir>::iterator toRemove = _bulletSprites.begin();

	for (list<balleEtDir>::iterator it = _bulletSprites.begin(); it != _bulletSprites.end(); it++)
	{
		if (it->live)
			it->balle.setPosition((*it).balle.getPosition().x + it->distX * dt, it->balle.getPosition().y + it->distY * dt);
		else
		{
			_bulletSprites.erase(it);
			break;
		}		
	}
}