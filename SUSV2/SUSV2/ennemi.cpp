/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette														*/
/* Nom         : ennemi.cpp                                                                 */
/* Date        : 21 decembre 2022                                                           */
/* But         : Gere un ennemi qui peut se deplacer et interagir avec des sprites			*/
/********************************************************************************************/

#include "ennemi.h"

using namespace sf;

// constructeur sans parametre
ennemi::ennemi(gameDataRef data) : _data(data)
{
	_move = true;
	_speed = 0;
	_pv = 0;
	_taille.x = 0;
	_taille.y = 0;
	_position.x = 0;
	_position.y = 0;
	_enVie = false;

	_spriteEnnemi.setTexture(_data->assets.getTexture("ennemi sprite sheet vivant"));
}

// destructeur d ennemi
ennemi::~ennemi()
{
	_move = true;
	_speed = 0;
	_pv = 0;
	_taille.x = 0;
	_taille.y = 0;
	_position.x = 0;
	_position.y = 0;
	_enVie = false;
}

// constructeur avec parametre
ennemi::ennemi(int speed, double pv, sf::Vector2f positionDepart, gameDataRef data) : _data(data)
{

	_move = true;
	_spriteEnnemi.setTexture(_data->assets.getTexture("ennemi sprite sheet vivant"));
	_speed = speed - rand() % 15;	//speed modifie pour pas qu'il soit tous pareil
	_pv = pv;
	_taille.x = 0;
	_taille.y = 0;
	_position.x = 0;
	_position.y = 0;
	_frameActuel = 0;
	_tempsAnimation = 0;
	_enVie = true;
	_position.x = 0;
	_position.y = 0;

	spawn(positionDepart);	// place dans la fenetre
}

// calcule la vie apres un hit
bool ennemi::touche(double damage)
{
	_pv -= damage;

	if (_pv <= 0)		// si mort
	{
		_enVie = false;
		_spriteEnnemi.setTexture(_data->assets.getTexture("ennemi sprite sheet mort"));
		IntRect rectSprite(0, 0, 32, 32);

		rectSprite.left = (rand() % 5) * 32;
		_spriteEnnemi.setTextureRect(rectSprite);

		return true;
	}

	return false;
}

// verifie si vivant
bool ennemi::estVivant() const
{
	return _enVie;
}

// place un ennemi dans la fenetre
void ennemi::spawn(sf::Vector2f positionDepart)
{
		_position.x = positionDepart.x;
		_position.y = positionDepart.y;
		_spriteEnnemi.setPosition(_position);
}

// donne la position en rectangle
FloatRect ennemi::getPosition()
{
	return _spriteEnnemi.getGlobalBounds();
}

// donne le sprite
Sprite ennemi::getSprite()
{
	return _spriteEnnemi;
}

// update l'ennemi
void ennemi::update(float variationTemps, Vector2f positionJoueur)
{
	float joueurPosX = positionJoueur.x;
	float joueurPosY = positionJoueur.y;

	_spriteEnnemi.setOrigin(_spriteEnnemi.getGlobalBounds().width / 2, _spriteEnnemi.getGlobalBounds().width / 2); // permet de centrer l'ennemi

	// Update la position des ennemis
	if (_move)	// si il a le droit de bouger
	{
		if (joueurPosX > _position.x)
		{
			_position.x = _position.x + _speed * variationTemps;
		}

		if (joueurPosY > _position.y)
		{
			_position.y = _position.y + _speed * variationTemps;
		}

		if (joueurPosX < _position.x)
		{
			_position.x = _position.x - _speed * variationTemps;
		}

		if (joueurPosY < _position.y)
		{
			_position.y = _position.y - _speed * variationTemps;
		}
	}

	// Bouge le sprite
	_spriteEnnemi.setPosition(_position);

	_tempsAnimation += variationTemps;

	// Change l'image
	setTextureAnimation(positionJoueur);
}

// modifie les stats
void ennemi::setEnnemi(int speed, double pv)
{
	_speed = speed - rand() % 30; // Modifie la speed de chaque pour qu'il ne se déplace pas tous en même temps
	_pv = pv;
	_enVie = true;
}

// modifie la texture 
void ennemi::setTextureAnimation(Vector2f positionJoueur)
{
	IntRect rectSprite(0, 0, 32, 32);

	Vector2f dirVec = Vector2f(positionJoueur.x - (_position.x + 16), positionJoueur.y - (_position.y + 16));

	// Calculale la longueur^2
	float magSquare = std::sqrt((dirVec.x * dirVec.x) + (dirVec.y * dirVec.y));


	dirVec.x = (dirVec.x) / magSquare;

	// L'angle et le change en degré
	float angle = std::acos(dirVec.x) * (180 / 3.141);          // 180 ----------- 0           direction angle 


	//regarde si on bouge
	bool mouvement;
	std::cout << "ennemi position x << " << _position.x << std::endl;
	std::cout << "ennemi position y << " << _position.y << std::endl;
	std::cout << "player position x << " << positionJoueur.x << std::endl;
	std::cout << "player position y << " << positionJoueur.y << std::endl;
	std::cout << "ennemi temps << " << _tempsAnimation << std::endl;

	if (positionJoueur == _position)
	{
		mouvement = false;
	}
	else
	{
		mouvement = true;
	}

	if (angle > 135) {   // Gauche

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
		_spriteEnnemi.setTextureRect(rectSprite);
	}

	if (angle < 135 && angle > 45 && _position.y < positionJoueur.y) { //bas

		if (_frameActuel >= _nbrImageBas - 1 || !mouvement)
		{
			_frameActuel = 0;
		}
		else if (_tempsAnimation >= _delaisEntreFrame)
		{
			_tempsAnimation = 0;
			_frameActuel++;
		}

		rectSprite.top = 96;
		rectSprite.left = _frameActuel * 32;
		_spriteEnnemi.setTextureRect(rectSprite);
	}

	if (angle < 45) {   //droite

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
		_spriteEnnemi.setTextureRect(rectSprite);
	}

	if (angle < 135 && angle > 45 && _position.y > positionJoueur.y) { // haut

		if (_frameActuel >= _nbrImageHaut - 1 || !mouvement)
		{
			_frameActuel = 0;
		}
		else if (_tempsAnimation >= _delaisEntreFrame)
		{
			_tempsAnimation = 0;
			_frameActuel++;
		}

		rectSprite.top = 64;
		rectSprite.left = _frameActuel * 32;
		_spriteEnnemi.setTextureRect(rectSprite);
	}

	std::cout << "ennemi animation << " << _frameActuel << std::endl;
}

// place la hitbox
void ennemi::setHitboxPos(sf::Vector2f pos)
{
	sf::FloatRect r(pos.x, pos.y, 16, 19);
	_hitbox = r;
}

// change la position
void ennemi::setPos(sf::Vector2f pos)
{
	_position = pos;
}

// bouge en haut
void ennemi::moveUp(float dt) {
	_position.y -= _speed * dt;
}

// bouge en bas
void ennemi::moveDown(float dt) {
	_position.y += _speed * dt;
}

// bouge a gauche
void ennemi::moveLeft(float dt) {
	_position.x -= _speed * dt;
}

// bouge a droite
void ennemi::moveRight(float dt) {
	_position.x += _speed * dt;
}

// set le droit de bouger
void ennemi::setMove(bool move) {
	_move = move;
}

// donne la taille
sf::Vector2u ennemi::getTaille()
{
	return _taille;
}

// donne la pos coord
sf::Vector2f ennemi::getVectPosition()
{
	return _position;
}

// donne la hit box en rect
sf::FloatRect ennemi::getRectShape()
{
	return _hitbox;
}

// copieur
const ennemi& ennemi::operator=(const ennemi& e)
{
	_speed = e._speed;
	_pv = e._pv;
	_taille = e._taille;
	_position = e._position;
	_enVie = e._enVie;
	_spriteEnnemi = e._spriteEnnemi;

	return *this;
}