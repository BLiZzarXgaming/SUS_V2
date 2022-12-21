#include "boss.h"

boss::boss(gameDataRef data) : _data(data) {
	_vie = 3;
	_damage = 1;
	_spriteTete.setTexture(_data->assets.getTexture("boss spritesheet"));
	_spriteCorps.setTexture(_data->assets.getTexture("boss spritesheet"));
	_spriteBras.setTexture(_data->assets.getTexture("boss spritesheet"));
	//_spriteAttaque.setTexture(_data->assets.getTexture("boss spritesheet"));
	_frameActuel = 0;
	_tempsAnimation = 0;
	_frameActuelCorps = 0;
	_frameActuelBras = 0;
	_frameActuelTete = 0;
	_typeAttaque = 0;
}

boss::~boss() {
	_vie = 0;
	_positionBoss.x = 0;
	_positionBoss.y = 0;
	_damage = 0;
}

void boss::setVie(int vie) {
	_vie = vie;
}

void boss::decVie()
{
	_vie--;
}

double boss::getVie()const {
	return _vie;
}

Sprite boss::getSpriteAttaque(){
	return _spriteAttaque;
}
Sprite boss::getSpriteTete() {
	return _spriteTete;
}
Sprite boss::getSpriteCorps() {
	return _spriteCorps;
}
Sprite boss::getSpriteBras() {
	return _spriteBras;
}

void boss::setSpriteAttaquePos(int x, int y) {
	_spriteAttaque.setPosition(x, y);
}

void boss::setSpriteTetePos(int x, int y) {
	_spriteTete.setPosition(x, y);
}

void boss::setSpriteCorpsPos(int x, int y) {
	_spriteCorps.setPosition(x, y);
}

void boss::setSpriteBrasPos(int x, int y) {
	_spriteBras.setPosition(x, y);
}

void boss::setHitboxPos(sf::Vector2f pos)
{
	sf::FloatRect r(pos.x, pos.y + 2, 288, 96);
	_hitbox = r;
}

void boss::setTypeAttaque(int index) {
	_typeAttaque = index;
}

sf::FloatRect boss::getRectShape()
{
	return _hitbox;
}

sf::Vector2f boss::getVectPosition()
{
	return _positionBoss;
}

void boss::update(float dtEnSeconde)
{

	_spriteCorps.setOrigin(_spriteCorps.getGlobalBounds().width / 2, _spriteCorps.getGlobalBounds().width / 2); //changer ca ?

	//_spriteCorps.setPosition(_positionBoss);
	//_spriteTete.setPosition(_positionBoss);
	//_spriteBras.setPosition(_positionBoss);

	_tempsAnimation += dtEnSeconde; // ajoute le temps passé au temps de l'animation

	setBossTexture(); // va updater la texture du boss
}

void boss::setBossTexture() {

	IntRect rectSprite(0, 0, 144, 80);
	IntRect rectSpriteBras(0, 0, 208, 48 );

	if (_typeAttaque == 0) {      //idle state
		_frameActuel = 0;
		_frameActuelBras = 0;
		_frameActuelCorps = 0;
		_frameActuelTete = 0;

		rectSprite.top = 240;						//corps
		rectSprite.left = _frameActuelCorps * 144;
		_spriteCorps.setTextureRect(rectSprite);

		rectSprite.top = 0;							//tete
		rectSprite.left = _frameActuelTete * 144;
		_spriteTete.setTextureRect(rectSprite);

		rectSpriteBras.top = 352;					//bras
		rectSpriteBras.left = _frameActuelBras * 208;
		_spriteBras.setTextureRect(rectSpriteBras);

		rectSprite.top = 80;						//attaque
		rectSprite.left = _frameActuelBras * 208;
		_spriteAttaque.setTextureRect(rectSprite);
		
	}
	else if (_typeAttaque == 1) {			//attaque de drones
		attaqueDrone(rectSprite, rectSpriteBras);
	}
	else if (_typeAttaque == 2) {			//attaque de laser
		attaqueLaser(rectSprite, rectSpriteBras);
	}
	else if (_typeAttaque == 3) {			//attaque missile
		attaqueMissile(rectSprite, rectSpriteBras);
	}
	else if (_typeAttaque = 4) {
		attaqueCoup(rectSprite, rectSpriteBras);
	}
}

void boss::attaqueDrone(IntRect rectSprite, IntRect rectSpriteBras) {
	if (_tempsAnimation >= _delaisEntreFrame && _frameActuelTete < _nbrNormalImage)		//fait toute les sprites de l'attaque
		_frameActuelTete++;
	else if (_tempsAnimation >= _delaisEntreFrame)			//fait en sorte de boucler les deux derniere frames de l'attaque 
		_frameActuelTete--;

	_tempsAnimation = 0;
	rectSprite.top = 0;
	rectSprite.left = _frameActuelTete * 288;
	_spriteTete.setTextureRect(rectSprite);
}

void boss::attaqueLaser(IntRect rectSprite, IntRect rectSpriteBras) {
	if (_tempsAnimation >= _delaisEntreFrame && _frameActuelTete < _nbrNormalImage)
	{
		
		if (_frameActuelTete == 7)
		{
			_frameActuelTete--;
			_frameActuel--;
		}
		else
		{
			_frameActuelTete++;
			_tempsAnimation = 0;
		}
		
	}		//fait toute les sprites de l'attaque
		
	else if (_tempsAnimation >= _delaisEntreFrame) {		//fait en sorte de boucler les deux derniere frames de l'attaque + le laser
		_frameActuelTete--;
		_frameActuel--;
	}			
	if (_frameActuelTete == 7)
		_frameActuel = 1;

	cout << "temps anim: " << _tempsAnimation << "  delai: " << _delaisEntreFrame << "  frame " << _frameActuelTete << endl;

	rectSprite.top = 160; //80
	rectSprite.left = _frameActuelTete * 144;
	_spriteTete.setTextureRect(rectSprite);
	//cout << _tempsAnimation << endl;
}

void boss::attaqueMissile(IntRect rectSprite, IntRect rectSpriteBras) {
	if (_tempsAnimation >= _delaisEntreFrame && _frameActuelTete < _nbrNormalImage)		//fait toute les sprites de l'attaque
		_frameActuelCorps++;
	_tempsAnimation = 0;

	rectSprite.top = 240;
	rectSprite.left = _frameActuelCorps * 144;
	_spriteCorps.setTextureRect(rectSprite);
}

void boss::attaqueCoup(IntRect rectSprite, IntRect rectSpriteBras) {
	if (_tempsAnimation >= _delaisEntreFrame && _frameActuelTete < _nbrNormalImage)		//fait toute les sprites de l'attaque
		_frameActuelCorps++;
	_tempsAnimation = 0;
	
	rectSpriteBras.top = 352;
	rectSpriteBras.left = _frameActuelBras * 208;
	_spriteBras.setTextureRect(rectSpriteBras);
}

void boss::draw() const
{
	_data->window.draw(_spriteCorps);
	_data->window.draw(_spriteTete);
	_data->window.draw(_spriteBras);
	_data->window.draw(_spriteAttaque);
}