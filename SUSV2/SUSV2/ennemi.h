/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette														*/
/* Nom         : ennemi.h                                                                   */
/* Date        : 21 decembre 2022                                                           */
/* But         : Gere un ennemi qui peut se deplacer et interagir avec des sprites			*/
/********************************************************************************************/
#pragma once
#include "SFML/Graphics.hpp"
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"

class ennemi
{
private:
	gameDataRef _data;

	int _speed;					// la vitesse
	double _pv;					// la vie
	sf::Vector2u _taille;		// la taille de l'ennemi
	sf::Vector2f _position;		// la position de l'ennemi en coordonne
	bool _enVie;				// si il est en vie
	sf::Sprite _spriteEnnemi;	// le sprite de l'ennemi
	sf::FloatRect _hitbox;		// la hitbox en rectangle
	bool _move;					// si il peut bouger

	// constante pour la spritesheet
	const int _nbrImageDroite = 7;
	const int _nbrImageGauche = 7;
	const int _nbrImageHaut = 4;
	const int _nbrImageBas = 4;

	int _frameActuel;																// l animation actuelle
	const double _delaisEntreFrame = 0.2;											// le délais entre les animations			
	double _tempsAnimation;															// le temps que l'animation dure


public:
	ennemi(gameDataRef data);														// constructeur sans parametre				
	ennemi(int speed, double pv, sf::Vector2f positionDepart, gameDataRef data);	// constructeur avec parametre
	~ennemi();																		// destructeur d ennemi

	bool touche(double damage);														// calcule la vie apres un hit
	bool estVivant() const;															// verifie si vivant

	void spawn(sf::Vector2f positionDepart);										// place un ennemi dans la fenetre

	sf::FloatRect getPosition();													// donne la position en rectangle
	sf::Sprite getSprite();															// donne le sprite

	void update(float variationTemps, sf::Vector2f positionJoueur);					// update l'ennemi

	void setEnnemi(int speed, double pv);											// modifie les stats 

	void setTextureAnimation(sf::Vector2f positionJoueur);							// modifie la texture 
	void setHitboxPos(sf::Vector2f);												// place la hitbox
	void setPos(sf::Vector2f);														// change la position

	void moveUp(float dt);															// bouge en haut
	void moveDown(float dt);														// bouge en bas
	void moveLeft(float dt);														// bouge a gauche
	void moveRight(float dt);														// bouge a droite
	void setMove(bool move);														// set le droit de bouger

	
	sf::Vector2u getTaille();														// donne la taille
	sf::Vector2f getVectPosition();													// donne la pos coord
	sf::FloatRect getRectShape();													// donne la hit box en rect

	const ennemi& operator=(const ennemi& e);										// copieur
};