#include "gameState.h"
#include <iostream>
//le constructeur utilise les : pour initialiser _data avant m�me l�ex�cution du contenu{}
gameState::gameState(gameDataRef data) : _data(data)
{
	_player = nullptr;
	_gameState = gameStates::ready;
	_hud = nullptr;
	
}

gameState::~gameState() {
	delete _player;
	delete _map;
	delete _hud;
}


void gameState::init()
{
	_data->assets.loadTexture("player sprite sheet", PLAYER_SPRITESHEET_FILEPATH);
	_player = new player(_data);

	_gameState = gameStates::ready;
  
	_data->assets.loadTexture("mapTileSet", MAP_TILESET_FILEPATH);
	_data->assets.loadTexture("main background", MAIN_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("main background"));
	_background.setPosition(100, -20);
	_background.setOrigin(250, 164);

	_player->setPos(64, 128, false);	//place le joueur dans la map


	_viewJoueur.setCenter(_player->getPosition().left + _player->getPosition().width / 2,
		_player->getPosition().top + _player->getPosition().height / 2);
	_viewJoueur.setSize(_data->window.getSize().x, _data->window.getSize().y);
	_viewJoueur.zoom(0.2f); // set le zoom de la view du joueur

	_data->assets.loadTexture("player healthbar", PLAYER_HEALTH_FILEPATH);

	_hud = new Hud(_data);
	
	_map = new gameMap(_data);

}

//fen�tre qui reste ouverte tant qu�elle n�est pas ferm�e
void gameState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
		else {

			if (Keyboard::isKeyPressed(Keyboard::W))	//move up avec W
				_player->moveUp();
			else
				_player->noMoveUp();


			if (Keyboard::isKeyPressed(Keyboard::A))	//move left avec A
				_player->moveLeft();
			else
				_player->noMoveLeft();


			if (Keyboard::isKeyPressed(Keyboard::S))	//move down avec S 
				_player->moveDown();
			else
				_player->noMoveDown();

			if (Keyboard::isKeyPressed(Keyboard::D))	//move right avec D
				_player->moveRight();
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
}
//aucune update
void gameState::update(float dt)
{
	//si ce n�est pas gameOver
	if (_gameState != gameStates::gameOver) {
		//rajouter un if qui dit a l'ennemie de se diriger vers le player si il est dans le range
	}
	//si c�est playing, on a cliqu�, donc on joue.

	if (_gameState == gameStates::playing) {

	}

	//METTRE LE CODE EN DESSOUS DANS LE IF() DU PLAYING LORSQUE LE MENU METTERA LE GAMESTATE A PLAYING

	_viewJoueur.setCenter(_player->getPosition().left + _player->getPosition().width / 2,
		_player->getPosition().top + _player->getPosition().height / 2);

	// Position de la souris dans le jeu
	_posSourisJeu = _data->window.mapPixelToCoords(
		Mouse::getPosition(), _viewJoueur);

	_player->setPosViseur(_posSourisJeu);
	_player->update(dt);

	for (int i = 0; i < _map->getWalls().size(); i++)
		if (_collision.checkSpriteCollision(_player->getSprite(), _map->getWalls().at(i))) {
			_player->setPos(_player->getMemoirePos());
			_player->setCanMove(false);
		}
		else if (i == 0) {
			_player->setCanMove(true);
			_player->cycleMemoirePos();
		}
	//cout << _player->getX() << "   " << _player->getY() << endl;

	if (_player->getY() > 150)		//fait en sorte que le background ne descende pas lorsque le joueur est bas dans la map
		_background.setPosition(_player->getX(), 150);
	else
	_background.setPosition(_player->getVectPosition());

	//_hud->setBalle(_player.getballe());  //RAJOUTER QUE L'ON PEUT ALLER CHERCHER LE NOMBRE DE BALLES
	_hud->updateVie(_player->getVie());
	_hud->setPosition(Vector2f(_player->getX() +75, _player->getY() +54));

	

	//-------JUSQU'ICI---------------------------------------------------
}

//clear, dessine le background et display la fen�tre. (dt n�est pas utilis� ici)
void gameState::draw(float dt) const
{
	_data->window.clear();	//nettoie la fenetre
	_data->window.setView(_viewJoueur);
	_data->window.draw(_background);
	_map->draw();
	_player->draw();
	_hud->draw();
	
	_data->window.display();	//affiche la frame
}