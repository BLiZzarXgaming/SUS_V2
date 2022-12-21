#pragma once
#include "SFML/Graphics.hpp"
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"

class ennemi
{
public:
	ennemi(gameDataRef data);
	ennemi(int speed, double pv, sf::Vector2f positionDepart, gameDataRef data);
	~ennemi();

	bool touche(double damage);
	bool estVivant();
	void spawn(sf::Vector2f positionDepart);
	sf::FloatRect getPosition();
	sf::Sprite getSprite();
	void update(float variationTemps, sf::Vector2f positionJoueur);
	void setEnnemi(int speed, double pv);
	void setTextureAnimation(sf::Vector2f positionJoueur);
	void setHitboxPos(sf::Vector2f);
	void setPos(sf::Vector2f);

	void moveUp(float dt);
	void moveDown(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);
	void setMove(bool move);

	const int _nbrImageDroite = 7;
	const int _nbrImageGauche = 7;
	const int _nbrImageHaut = 4;
	const int _nbrImageBas = 4;
	int _frameActuel;
	const double _delaisEntreFrame = 0.2; // le délais entre les animations
	double _tempsAnimation; // le temps que l'animation dure

	sf::Vector2u getTaille();
	sf::Vector2f getVectPosition();
	sf::FloatRect getRectShape();

	const ennemi& operator=(const ennemi& e);

	

private:
	gameDataRef _data;
	int _speed;
	double _pv;
	sf::Vector2u _taille;
	sf::Vector2f _position;
	bool _enVie;
	sf::Sprite _spriteEnnemi;
	sf::FloatRect _hitbox;
	bool _move;
};