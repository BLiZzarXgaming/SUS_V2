/********************************************************************************************/
/* Auteur      : Xavier Caouette, Louis-Philippe Racette									                  */
/* Nom         : player.h                                                                   */
/* Date        : 21 decembre 2022                                                           */
/* But         : gestion d un joueur et de son affichage									                  */
/********************************************************************************************/
#pragma once
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class player
{
private:
	gameDataRef _data;

	double _vie;														// la vie actuelle
	double _vieMax;														// la vie max

	int _reloadTime;													// le temps de reload
	int _frameInv;														// temps invincible

	sf::Vector2f _positionJoueur;										// postion du joueur coords
	int _speed;															// la vitesse
	int _damage;														// les degats
	bool _direction, _haut = false, _bas = false, _droite = false, _gauche = false;	// les directions de mouvement
	sf::Vector2f _vraiDir;															// direction vise
	int _directionEnumHB;															// enum haut bas
	int _directionEnumGD;															// enum gauche droite
	int _nbrBalleReste;																// nbr de balle qui reste
	int _balleActuel;																// la balle actuel
	bool _canMove;																	// si il peut bouger
  int _score;
	
	sf::Sprite _sprite;																// sprite viseur										
	sf::Vector2f _posViseur;														// la position du viseur

	sf::Sprite _viseur;																// le sprite du viseur

	// variable sprite sheet
	const int _nbrImageDroite = 7;
	const int _nbrImageGauche = 7;
	const int _nbrImageHaut = 4;
	const int _nbrImageBas = 4;

	int _frameActuel;
	const double _delaisEntreFrame = 0.1;											// le delais entre les animations
	double _tempsAnimation;															// le temps que l'animation dure

	sf::FloatRect _hitbox;															// les hit box en rectangle
		
	std::queue<Vector2f> _memoirePos;												// une structure de queue pour garder en 
																					// memoire quelques positions du joueur
																					// (utilisé pour les collisions)

public:
	player(gameDataRef data);														// constructeur
	~player();																		// destructeur

	void setVie(int vie);															// set la vie
	void decVie();																	// enleve une vie
	void setMaxVie(double vieMax);													// set la vie max

	void decFrameInv();																// enleve une frame d invincibilite
	void setFrameInv(int);															// ajoute une frame d invincibilite
	void setX(double posX);															// set la position x du joueur
	void setY(double posY);															// set la position y du joueur
	void setDir(bool direction);													// set la direction du joueur
	void setDamage(double damage);													// set les degat
	void setPos(double posX, double posY, bool direction);							// set la position et la direction
	void setPos(sf::Vector2f);														// set la position
	void setPosViseur(sf::Vector2f posViseur);										// set la position du viseur
	void setReloadTime(int);														// set le reload time
	void decReloadTime();															// diminue le reload time
	void setHitboxPos(sf::Vector2f);												// set la position de la hit box
	void cycleMemoirePos();															// garde en memoire la position anterieur
	void setCanMove(bool);															// set si peut bouger
	void setDirectionEnumHB(int);													// set enum haut bas
	void setDirectionEnumGD(int);													// set enumgauche droite

	double getVie()const;															// donne la vie actuelle
	double getMaxVie() const;														// donne la vie max 
	int getFrameInvTime();															// donne les frames d invincibilite
	double getX()const;																// donne la position x du sprite
	double getY()const;																// donne la position y du sprite
	sf::Sprite getSprite() const;													// donne le sprite
	sf::FloatRect getPosition();													// donne la position en rect
	sf::Vector2f getVraiDir();														// donne la direction vise
	int getReloadTime();															// donne la valeur de reload
	sf::FloatRect getRectShape();													// donne la shape rectangulaire
	sf::Vector2f getVectPosition();													// donne la position du joueur coords
	sf::Vector2f getMemoirePos() const;												// donne la position du joueur en memoire
	int getDirectionEnumHB()const;													// donne enum haut bas
	int getDirectionEnumGD()const;													// donne enum haut bas
  int getScore()const;                                    // donne le score

	bool getCanMove()const;															// donne si on peut bouger
	void moveUp();																	// bouge le joueur en haut
	void moveDown();																// bouge le joueur en bas
	void moveRight();																// bouge le joueur a droite
	void moveLeft();																// bouge le joueur a gauche

	void noMoveUp();																// empeche de bouger en haut
	void noMoveDown();																// empeche de bouger en bas
	void noMoveRight();																// empeche de bouger a droite
	void noMoveLeft();																// empeche de bouger a gauche

	void update(float dt);															// update le joueur
	void setPlayerTexture();														// modifie la texture du joueur

	void reload();																	// reload les balles

	void draw() const;																// dessine le joueur
};