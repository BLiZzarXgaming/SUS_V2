#include "gameState.h"
#include <iostream>
//le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
gameState::gameState(gameDataRef data) : _data(data)
{
	_player = nullptr;
	_gameState = gameStates::ready;
}

gameState::~gameState() {
	delete _player;
}


void gameState::init()
{
	_data->assets.loadTexture("player sprite sheet", PLAYER_SPRITESHEET_FILEPATH);

	_player = new player(_data);

	_gameState = gameStates::ready;

}

//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
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
		}
	}
}
//aucune update
void gameState::update(float dt)
{
	//si ce n’est pas gameOver
	if (_gameState != gameStates::gameOver) {
		//rajouter un if qui dit a l'ennemie de se diriger vers le player si il est dans le range
	}
	//si c’est playing, on a cliqué, donc on joue.

	if (_gameState == gameStates::playing) {

	}

	//METTRE LE CODE EN DESSOUS DANS LE IF() DU PLAYING LORSQUE LE MENU METTERA LE GAMESTATE A PLAYING

	_viewJoueur.setCenter(Vector2f(_player->getPosition().left + _player->getPosition().width / 2,
		_player->getPosition().top + _player->getPosition().height / 2));

	// Position de la souris dans le jeu
	_posSourisJeu = _data->window.mapPixelToCoords(
		Mouse::getPosition(), _viewJoueur);

	_viewJoueur.setCenter(_player->getPosition().left + _player->getPosition().width / 2,
		_player->getPosition().top + _player->getPosition().height / 2);
	_player->setPosViseur(_posSourisJeu);
	_player->update(dt);
	
	_viewJoueur.setSize(_data->window.getSize().x, _data->window.getSize().y);

	cout << _player->getX() << "   " << _player->getY() << endl;

	//-------JUSQU'ICI---------------------------------------------------
}
//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void gameState::draw(float dt) const
{
	_data->window.clear();

	_data->window.setView(_viewJoueur);
	_player->draw();
	_data->window.display();
}