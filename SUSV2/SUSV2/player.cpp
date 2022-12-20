#include "player.h"

player::player(gameDataRef data) : _data(data) {
	_vie = 3;
	_vieMax = 3;
	_positionJoueur.x = 0;
	_positionJoueur.y = 0;
	_direction = false;
	_damage = 1;
	_speed = 0;
	_sprite.setTexture(_data->assets.getTexture("player sprite sheet"));
	_frameActuel = 0;
	_tempsAnimation = 0;
	_balleActuel = 0;
	_nbrBalleReste = 0;
}

player::~player() {
	_vie = 0;
	_positionJoueur.x = 0;
	_positionJoueur.y = 0;
	_direction = false;
	_damage = 0;
}

void player::setVie(int vie) {
	_vie = vie;
}

void player::setMaxVie(double vieMax)
{
	_vieMax = vieMax;
}

void player::decVie()
{
	_vie--;
}

void player::setX(double posX) {
	_positionJoueur.x = posX;
}

void player::setY(double posY) {
	_positionJoueur.y = posY;
}

void player::setDir(bool direction) {
	_direction = direction;
}

void player::decFrameInv()
{
	_frameInv--;
}

void player::setDamage(double damage) {
	_damage = damage;
}

void player::setFrameInv(int temps)
{
	_frameInv = temps;
}

void player::setPos(double posX, double posY, bool direction) {
	setX(posX);
	setY(posY);
	setDir(direction);
}

void player::setPosViseur(sf::Vector2f posViseur)
{
	_posViseur = posViseur;
}

void player::setReloadTime(int time)
{
	_reloadTime = time;
}

double player::getVie()const {
	return _vie;
}

void player::decReloadTime()
{
	_reloadTime--;
}

double player::getMaxVie() const
{
	return _vieMax;
}

double player::getX()const
{
	return _positionJoueur.x;
}

void player::setHitboxPos(sf::Vector2f pos)
{
	sf::FloatRect r(pos.x, pos.y+2, 16, 5);
	_hitbox = r;
}

double player::getY()const
{
	return _positionJoueur.y;
}

sf::Sprite player::getSprite() const // pour pouvoir le dessiner
{
	return _sprite;
}

sf::FloatRect player::getPosition() // pour les collisions
{
	return _sprite.getGlobalBounds();
}

sf::Vector2f player::getVraiDir()
{
	return _vraiDir;
}

int player::getReloadTime()
{
	return _reloadTime;
}

void player::moveUp()
{
	_haut = true;
}

void player::moveDown()
{
	_bas = true;
}

int player::getFrameInvTime()
{
	return _frameInv;
}

void player::moveRight()
{
	_droite = true;
}

sf::FloatRect player::getRectShape()
{
	return _hitbox;
}

void player::moveLeft()
{
	_gauche = true;
}

bool player::collisionMur()
{
	return false;
}

void player::noMoveUp()
{
	_haut = false;
}

sf::Vector2f player::getVectPosition()
{
	return _positionJoueur;
}

void player::noMoveDown()
{
	_bas = false;
}

void player::noMoveRight()
{
	_droite = false;
}

void player::noMoveLeft()
{
	_gauche = false;
}

void player::update(float dtEnSeconde)
{
	if ((_haut && _droite) || (_haut && _gauche) || (_bas && _droite) || (_bas && _gauche)) //Permet de ne pas courrir 2x plus vite en diagonal
		_speed = 50;
	else
		_speed = 80;

	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().width / 2); // permet de centrer l'ennemi
	if (_haut) {
		_positionJoueur.y -= _speed * dtEnSeconde;
	}
	if (_bas) {
		_positionJoueur.y += _speed * dtEnSeconde;
	}
	if (_gauche) {
		_positionJoueur.x -= _speed * dtEnSeconde;
	}
	if (_droite) {
		_positionJoueur.x += _speed * dtEnSeconde;
	}

	_sprite.setPosition(_positionJoueur);

	_tempsAnimation += dtEnSeconde; // ajoute le temps passé au temps de l'animation

	setPlayerTexture(); // va updater la texture du joueur
}

void player::setPlayerTexture() {

	IntRect rectSprite(0, 0, 32, 32);
	//_sprite.setTextureRect(rectSprite);

	Vector2f dirVec = Vector2f(_posViseur.x - (_positionJoueur.x + 16), _posViseur.y - (_positionJoueur.y + 16));

	//Calculale la longueur^2
	float magSquare = std::sqrt((dirVec.x * dirVec.x) + (dirVec.y * dirVec.y));

	dirVec.x = (dirVec.x) / magSquare;

	//l'angle et le change en degré
	float angle = std::acos(dirVec.x) * (180 / 3.141);          // 180 ----------- 0           direction angle 

	//regarde si on bouge
	bool mouvement;

	if (!_haut && !_bas && !_droite && !_gauche)
	{
		mouvement = false;
	}
	else
	{
		mouvement = true;
	}

	if (angle > 135) {      //Gauche

		if (_frameActuel >= _nbrImageGauche - 1 || !mouvement)
		{
			_frameActuel = 0;
		}
		else if (_tempsAnimation >= _delaisEntreFrame)
		{
			_tempsAnimation = 0;
			_frameActuel++;
		}

		rectSprite.top = 32;
		rectSprite.left = _frameActuel * 32;
		_sprite.setTextureRect(rectSprite);
		_vraiDir = Vector2f(-12, 5);
	}

	if (angle < 135 && angle > 45 && _positionJoueur.y < _posViseur.y) { // Bas

		if (_frameActuel >= _nbrImageBas - 1 || !mouvement)
		{
			_frameActuel = 1;
		}
		else if (_tempsAnimation >= _delaisEntreFrame)
		{
			_tempsAnimation = 0;
			_frameActuel++;
		}

		rectSprite.top = 32;
		rectSprite.left = (_frameActuel * 32) + 224;
		_sprite.setTextureRect(rectSprite);
		_vraiDir = Vector2f(4, 10);
	}

	if (angle < 45) {                                                  // Droite

		if (_frameActuel >= _nbrImageDroite - 1 || !mouvement)
		{
			_frameActuel = 0;
		}
		else if (_tempsAnimation >= _delaisEntreFrame)
		{
			_tempsAnimation = 0;
			_frameActuel++;
		}

		rectSprite.top = 0;
		rectSprite.left = _frameActuel * 32;
		_sprite.setTextureRect(rectSprite);
		_vraiDir = Vector2f(12, 5);
	}

	if (angle < 135 && angle > 45 && _positionJoueur.y > _posViseur.y) { // Haut

		if (_frameActuel >= _nbrImageHaut - 1 || !mouvement)
		{
			_frameActuel = 1;
		}
		else if (_tempsAnimation >= _delaisEntreFrame)
		{
			_tempsAnimation = 0;
			_frameActuel++;
		}

		rectSprite.top = 0;
		rectSprite.left = (_frameActuel * 32) + 224;
		_sprite.setTextureRect(rectSprite);
		_vraiDir = Vector2f(-9, -2);
	}
}

void player::setHud()
{

}

void player::reload() {
	_balleActuel = 0;
	_nbrBalleReste = 15;

	setReloadTime(100);
}

void player::draw() const
{
	_data->window.draw(_sprite);
}