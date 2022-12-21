﻿#include "bossFightState.h"
#include <iostream>

bossFightState::bossFightState(gameDataRef data, int score) : _data(data), _score(score)
{
	_player = nullptr;
	_gameState = gameStates::ready;
	_hud = nullptr;
	_boss = nullptr;
	_balle = nullptr;
	_score = score;
}

bossFightState::~bossFightState() {
	delete _player;
	delete _map;
	delete _hud;
	delete _boss;
	delete _balle;
}

void bossFightState::init()
{
	_data->assets.loadTexture("player sprite sheet", PLAYER_SPRITESHEET_FILEPATH);
	_player = new player(_data);

	_gameState = gameStates::playing;

	_data->assets.loadTexture("mapTileSet", MAP_TILESET_FILEPATH);
	_data->assets.loadTexture("main background", MAIN_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("main background"));
	_background.setPosition(128,20);
	_background.setOrigin(250, 164);

	_player->setPos(196, 64,false);	//place le joueur dans la map

	_viewJoueur.setCenter(_player->getPosition().left + _player->getPosition().width / 2,
		_player->getPosition().top + _player->getPosition().height / 2);
	_viewJoueur.setSize(_data->window.getSize().x, _data->window.getSize().y);
	_viewJoueur.zoom(0.25f); // set le zoom de la view du joueur

	_data->assets.loadTexture("player healthbar", PLAYER_HEALTH_FILEPATH);
	_data->assets.loadTexture("boss spritesheet", BOSS_SPRITESHEET_FILEPATH);

	_boss = new boss(_data);

	_hud = new Hud(_data);
	_balle = new bullet(_data);
	_data->assets.loadTexture("bullet", BULLET_FILEPATH);
	_map = new gameMap(_data, 1, -64, 29);
	
	_boss->setTypeAttaque(0);
	_boss->setBossTexture();
	
	

	_boss->setSpriteCorpsPos(176, 21);
	_boss->setSpriteBrasPos(72, 0);
	_boss->setSpriteTetePos(104, -82);

	_collidingWallID = 0;
	_lastShot.Zero;
}

//fen�tre qui reste ouverte tant qu�elle n�est pas ferm�e
void bossFightState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
		else {
			if (Keyboard::isKeyPressed(Keyboard::W) && _player->getCanMove()) {	//move up avec W
				_player->moveUp();
				_player->setDirectionEnumHB(directionEnumHB::haut);
			}
			else
				_player->noMoveUp();

			if (Keyboard::isKeyPressed(Keyboard::A) && _player->getCanMove()) {	//move left avec A
				_player->moveLeft();
				_player->setDirectionEnumGD(directionEnumGD::gauche);
			}
			else
				_player->noMoveLeft();

			if (Keyboard::isKeyPressed(Keyboard::S) && _player->getCanMove()) {	//move down avec S 
				_player->moveDown();
				_player->setDirectionEnumHB(directionEnumHB::bas);
			}
			else
				_player->noMoveDown();

			if (Keyboard::isKeyPressed(Keyboard::D) && _player->getCanMove()) {	//move right avec D
				_player->moveRight();
				_player->setDirectionEnumGD(directionEnumGD::droite);
			}
			else
				_player->noMoveRight();

			if (Mouse::isButtonPressed(Mouse::Left)) {	//tirer avec clique gauche

			}

			if (Keyboard::isKeyPressed(Keyboard::R)) {	//recharge avec R
				_player->reload();
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				_data->window.close();
			}


		}
	}

	if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S))
	{
		_player->setDirectionEnumHB(directionEnumHB::nohb);
		_player->noMoveDown();
		_player->noMoveUp();
	}

	if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
	{
		_player->setDirectionEnumGD(directionEnumGD::nogd);
		_player->noMoveRight();
		_player->noMoveLeft();
	}

	if (Mouse::isButtonPressed(Mouse::Left)) {	//tirer avec clique gauche
		if (_dureeJeu.asMilliseconds() - _lastShot.asMilliseconds() > 250)
		{
			_balle->tirer(_player->getVectPosition(), _posSourisJeu);
			_lastShot = _dureeJeu;
		}
			

		//cout << "duree: " << _dureeJeu.asMilliseconds() << "  last: " << 
	}
}
//aucune update
void bossFightState::update(float dt)
{
	//si ce n�est pas gameOver
	if (_gameState != gameStates::gameOver) {
		//rajouter un if qui dit a l'ennemie de se diriger vers le player si il est dans le range
	}
	//si c�est playing, on a cliqu�, donc on joue.

	if (_gameState == gameStates::playing)
	{
		_boss->setBossTexture();
	}
	//METTRE LE CODE EN DESSOUS DANS LE IF() DU PLAYING LORSQUE LE MENU METTERA LE GAMESTATE A PLAYING

	//  le temps écoulé entre deux frames pis se remet à zéro
	_variationTemps = _clock.restart();

	// additionne le temps total du jeu (intéressant pour des statistiques)
	_dureeJeu += _variationTemps;

	// Position de la souris dans le jeu
	_posSourisJeu = _data->window.mapPixelToCoords(
		Mouse::getPosition(), _viewJoueur);

	_player->setPosViseur(_posSourisJeu);
	_player->update(dt);

	_balle->update(dt);

	_boss->setTypeAttaque(2);
	_boss->setBossTexture();

	for (list<balleEtDir>::iterator it = _balle->getBulletSprites().begin(); it != _balle->getBulletSprites().end(); it++)
		if (_collision.checkSpriteCollision(_boss->getSpriteTete(), 0.8f, it->balle, 1))
		{
			_gameState = gameStates::gameWin;
			it->live = false;
		}
	if (_gameState == gameStates::gameWin) {
			_data->machine.addState(stateRef(new gameWinState(_data, _score)), true);
	}

	for (int i = 0; i < _map->getWalls().size(); i++)
		if (_collision.checkSpriteCollision(_player->getSprite(), 0.6f, _map->getWalls().at(i), 1)) {
			_player->setCanMove(false);
			_collidingWallID = 1 + _map->getWalls().at(i).getTextureRect().left / 32;
			if (_collidingWallID == 5 ||
				_collidingWallID == 17 ||
				_collidingWallID == 18 ||
				_collidingWallID == 19 ||
				_collidingWallID == 20 ||
				_collidingWallID == 11 ||
				_collidingWallID == 12 ||
				_collidingWallID == 15 ||
				_collidingWallID == 16)
			{
				_player->moveDown();
			}

			else if (_collidingWallID == 7)
				_player->moveRight();
			else if (_collidingWallID == 6)
				_player->moveLeft();
			else
				_player->moveUp();
		}
		else if (i == 0) {
			_player->setCanMove(true);
		}

	//_hud->setBalle(_player.getballe());  //RAJOUTER QUE L'ON PEUT ALLER CHERCHER LE NOMBRE DE BALLES
	_hud->updateVie(_player->getVie());
	_hud->setPosition(Vector2f(_player->getX() + 75, _player->getY() + 54));

	_boss->update(dt);
}

//-------JUSQU'ICI---------------------------------------------------


void bossFightState::draw(float dt) const
{
	_data->window.clear();	//nettoie la fenetre
	_data->window.setView(_viewJoueur);
	_data->window.draw(_background);
	_map->draw();
	_player->draw();
	_boss->draw();
	_hud->draw();
	_balle->draw();
	_data->window.display();	//affiche la frame
}