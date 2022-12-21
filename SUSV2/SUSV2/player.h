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
	Sprite _playerSprite;

	double _vie;
	double _vieMax;
	int _reloadTime;
	int _frameInv;
	sf::Vector2f _positionJoueur;
	int _speed;
	int _damage;
	bool _direction, _haut = false, _bas = false, _droite = false, _gauche = false;
	sf::Vector2f _vraiDir;
	int _directionEnumHB;
	int _directionEnumGD;
	int _nbrBalleReste;
	int _balleActuel;
	bool _canMove;

	sf::Sprite _sprite;
	sf::Texture _playerTexture;
	sf::Vector2f _posViseur;

	sf::Texture _textViseur;
	sf::Sprite _viseur;

	const int _nbrImageDroite = 7;
	const int _nbrImageGauche = 7;
	const int _nbrImageHaut = 4;
	const int _nbrImageBas = 4;
	int _frameActuel;
	const double _delaisEntreFrame = 0.1; // le delais entre les animations
	double _tempsAnimation;				  // le temps que l'animation dure

	sf::FloatRect _hitbox;

	std::queue<Vector2f> _memoirePos;	// une structure de queue pour garder en 
										// memoire quelques positions du joueur
										// (utilisé pour les collisions)

public:
	player(gameDataRef data);
	~player();

	void setVie(int vie);
	void decVie();
	void setMaxVie(double vieMax);

	void decFrameInv();
	void setFrameInv(int);
	void setX(double posX);
	void setY(double posY);
	void setDir(bool direction);
	void setDamage(double damage);
	void setPos(double posX, double posY, bool direction);
	void setPos(sf::Vector2f);
	void setPosViseur(sf::Vector2f posViseur);
	void setReloadTime(int);
	void decReloadTime();
	void setHitboxPos(sf::Vector2f);
	void cycleMemoirePos();
	void setCanMove(bool);
	void setDirectionEnumHB(int); //haut bas
	void setDirectionEnumGD(int); //gauche droite

	double getVie()const;
	double getMaxVie() const;
	int getFrameInvTime();
	double getX()const;
	double getY()const;
	sf::Sprite getSprite() const;
	sf::FloatRect getPosition();
	sf::Vector2f getVraiDir();
	int getReloadTime();
	sf::FloatRect getRectShape();
	sf::Vector2f getVectPosition();
	sf::Vector2f getMemoirePos() const;
	int getDirectionEnumHB()const;
	int getDirectionEnumGD()const;
	bool getCanMove()const;

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	//void update();
	void noMoveUp();
	void noMoveDown();
	void noMoveRight();
	void noMoveLeft();
	void update(float dt);
	void setPlayerTexture();

	bool collisionMur();
	void setHud();

	void reload();

	void draw() const;
};