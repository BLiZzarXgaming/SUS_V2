/********************************************************************************************/
/* Auteur      : Xavier Caouette, Louis-Philippe Racette									*/
/* Nom         : player.cpp                                                                 */
/* Date        : 21 decembre 2022                                                           */
/* But         : gestion d un joueur et de son affichage									*/
/********************************************************************************************/
#include "player.h"

// constructeur
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
	_canMove = true;
}

// destructeur
player::~player() {
	_vie = 0;
	_positionJoueur.x = 0;
	_positionJoueur.y = 0;
	_direction = false;
	_damage = 0;
}

// set la vie
void player::setVie(int vie) {
	_vie = vie;
}

// enleve une vie
void player::decVie()
{
	_vie--;
}

// set la vie max
void player::setMaxVie(double vieMax)
{
	_vieMax = vieMax;
}

// enleve une frame d invincibilite
void player::setFrameInv(int temps)
{
	_frameInv = temps;
}

// ajoute une frame d invincibilite
void player::decFrameInv()
{
	_frameInv--;
}

// set la position x du joueur
void player::setX(double posX) {
	_positionJoueur.x = posX;
}

// set la position y du joueur
void player::setY(double posY) {
	_positionJoueur.y = posY;
}

// set la direction du joueur
void player::setDir(bool direction) {
	_direction = direction;
}

// set les degat
void player::setDamage(double damage) {
	_damage = damage;
}

// set la position et la direction
void player::setPos(double posX, double posY, bool direction) {
	setX(posX);
	setY(posY);
	setDir(direction);
}

// set la position
void player::setPos(sf::Vector2f pos)
{
	setX(pos.x);
	setY(pos.y);
}

// set la position du viseur
void player::setPosViseur(sf::Vector2f posViseur)
{
	_posViseur = posViseur;
}

// set le reload time
void player::setReloadTime(int time)
{
	_reloadTime = time;
}

// diminue le reload time
void player::decReloadTime()
{
	_reloadTime--;
}

// set la position de la hit box
void player::setHitboxPos(sf::Vector2f pos)
{
	sf::FloatRect r(pos.x, pos.y+2, 16, 5);
	_hitbox = r;
}

// garde en memoire la position anterieur
void player::cycleMemoirePos()
{
	_memoirePos.push(_positionJoueur);

	if (_memoirePos.size() > 8)
		_memoirePos.pop();
}

// set si peut bouger
void player::setCanMove(bool can)
{
	_canMove = can;
}

// set enum haut bas
void player::setDirectionEnumHB(int dir)
{
	_directionEnumHB = dir;
}

// set enumgauche droite
void player::setDirectionEnumGD(int dir)
{
	_directionEnumGD = dir;
}


// donne la vie actuelle
double player::getVie()const {
	return _vie;
}

// donne la vie max 
double player::getMaxVie() const
{
	return _vieMax;
}

// donne les frames d invincibilite
int player::getFrameInvTime()
{
	return _frameInv;
}

// donne la position x du sprite
double player::getX()const
{
	return _positionJoueur.x;
}

// donne la position y du sprite

void player::setScore(int score)
{
	_score = score;
}

double player::getY()const
{
	return _positionJoueur.y;
}

// donne le sprite
sf::Sprite player::getSprite() const // pour pouvoir le dessiner
{
	return _sprite;
}

// donne la position en rect
sf::FloatRect player::getPosition() // pour les collisions
{
	return _sprite.getGlobalBounds();
}

// donne la direction vise
sf::Vector2f player::getVraiDir()
{
	return _vraiDir;
}

// donne la valeur de reload
int player::getReloadTime()
{
	return _reloadTime;
}

// donne la shape rectangulaire
sf::FloatRect player::getRectShape()
{
	return _hitbox;
}

// donne la position du joueur coords
sf::Vector2f player::getVectPosition()
{
	return _positionJoueur;
}

// donne la position du joueur en memoire
sf::Vector2f player::getMemoirePos() const
{
	return _memoirePos.front();
}

// donne enum haut bas
int player::getDirectionEnumHB() const
{
	return _directionEnumHB;
}

// donne enum haut bas
int player::getDirectionEnumGD() const
{
	return _directionEnumGD;
}

// donne si on peut bouger
bool player::getCanMove() const
{
	return _canMove;
}

// bouge le joueur en haut
void player::moveUp()
{
	_haut = true;
}

// bouge le joueur en bas
void player::moveDown()
{
	_bas = true;
}

// bouge le joueur a droite
void player::moveRight()
{
	_droite = true;
}

// bouge le joueur a gauche
void player::moveLeft()
{
	_gauche = true;
}

// empeche de bouger en haut
void player::noMoveUp()
{
	_haut = false;
}

// donne le score
int player::getScore() const
{
	return _score;
}

// empeche de bouger en bas
void player::noMoveDown()
{
	_bas = false;
}

// empeche de bouger a droite
void player::noMoveRight()
{
	_droite = false;
}

// empeche de bouger a gauche
void player::noMoveLeft()
{
	_gauche = false;
}

// update le joueur
void player::update(float dtEnSeconde)
{
	if ((_haut && _droite) || (_haut && _gauche) || (_bas && _droite) || (_bas && _gauche)) //Permet de ne pas courrir 2x plus vite en diagonal
		_speed = 50; //normalement 50
	else
		_speed = 80; //normalement 80

	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().width / 2);	// permet de centrer l'ennemi

	if ((_haut && !_bas) || (!_canMove && getDirectionEnumHB() == directionEnumHB::bas)) {			// en bas
		_positionJoueur.y -= _speed * dtEnSeconde;
		//cout << "  HAUT: " << _haut;
	}
	if ((_bas && !_haut) || (!_canMove && getDirectionEnumHB() == directionEnumHB::haut)) {			// en haut
		_positionJoueur.y += _speed * dtEnSeconde;
		//cout << "  BAS: " << _bas;
	}
	if ((_gauche && !_droite) || (!_canMove && getDirectionEnumGD() == directionEnumGD::droite)) {	// a droite
		_positionJoueur.x -= _speed * dtEnSeconde;
		//cout << "  GAUCHE: " << _gauche;
	}
	if ((_droite && !_gauche) || (!_canMove && getDirectionEnumGD() == directionEnumGD::gauche)) {	// a gauche
		_positionJoueur.x += _speed * dtEnSeconde;
		//cout << "  DOITE: " << _droite;
	}
	_sprite.setPosition(_positionJoueur);

	_tempsAnimation += dtEnSeconde; // ajoute le temps passé au temps de l'animation

	setPlayerTexture(); // va updater la texture du joueur
}

// modifie la texture du joueur
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

		if (_frameActuel >= _nbrImageDroiteetGauche - 1 || !mouvement)
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

		if (_frameActuel >= _nbrImageHautetBas - 1 || !mouvement)
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

		if (_frameActuel >= _nbrImageDroiteetGauche - 1 || !mouvement)
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

		if (_frameActuel >= _nbrImageHautetBas - 1 || !mouvement)
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

// reload les balles
void player::reload() {
	_balleActuel = 0;
	_nbrBalleReste = 15;

	setReloadTime(100);
}

// dessine le joueur
void player::draw() const
{
	_data->window.draw(_sprite);
}