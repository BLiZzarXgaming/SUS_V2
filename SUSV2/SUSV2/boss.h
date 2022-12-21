#pragma once

#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class boss
{
private:
	gameDataRef _data;
	Sprite _spriteAttaque, _spriteCorps, _spriteTete, _spriteBras;
	
	double _vie;

	sf::Vector2f _positionBoss;
	int _damage;

	sf::Texture _bossTexture;

	const int _nbrNormalImage = 8;
	int _frameActuel, _frameActuelCorps, _frameActuelBras, _frameActuelTete;
	const double _delaisEntreFrame = 0.2; // le delais entre les animations
	double _tempsAnimation;				  // le temps que l'animation dure

	int _typeAttaque;

	sf::FloatRect _hitbox;

	

public:
	boss(gameDataRef data);
	~boss();

	void setVie(int vie);
	void decVie();

	void setHitboxPos(Vector2f);

	double getVie()const;
	

	Sprite getSpriteAttaque();
	Sprite getSpriteTete();
	Sprite getSpriteCorps();
	Sprite getSpriteBras();

	void setSpriteAttaquePos(int x, int y);
	void setSpriteTetePos(int x, int y);
	void setSpriteCorpsPos(int x, int y);
	void setSpriteBrasPos(int x, int y);

	void setTypeAttaque(int index);


	FloatRect getPositionAttaque();
	FloatRect getRectShape();
	Vector2f getVectPosition();

	//void update();
	void update(float dt);
	void setBossTexture();

	void attaqueDrone(IntRect rectSprite, IntRect rectSpriteBras);
	void attaqueLaser(IntRect rectSprite, IntRect rectSpriteBras);
	void attaqueMissile(IntRect rectSprite, IntRect rectSpriteBras);
	void attaqueCoup(IntRect rectSprite, IntRect rectSpriteBras);

	void draw() const;
};