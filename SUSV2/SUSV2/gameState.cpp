#include "gameState.h"
#include <iostream>
//le constructeur utilise les : pour initialiser _data avant m�me l execution du contenu{}
gameState::gameState(gameDataRef data) : _data(data)
{
	_player = nullptr;
	_gameState = gameStates::ready;
	_hud = nullptr;
	_balle = nullptr;
	
}

gameState::~gameState() {
	delete _player;
	delete _map;
	delete _hud;
	delete _balle;
}


void gameState::init()
{
	//active le random 
	srand(time(NULL));

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

	_collidingWallID = 0;


	// pour ennemi les textures
	_data->assets.loadTexture("ennemi sprite sheet vivant", ENNEMI_SPRITESHEET_FILEPATH_VIVANT);
	_data->assets.loadTexture("ennemi sprite sheet mort", ENNEMI_SPRITESHEET_FILEPATH_MORT);


	_ennemis.reserve(NBR_ENNEMI_MAX);
	// TODO les placer dans la map
	//rempli le vecteur d'ennemi
	for (int i = 0; i < NBR_ENNEMI_MAX; i++)
	{
		ennemi* temp = new ennemi(40, 10, Vector2f(64, 148), _data);
		_ennemis.push_back(temp);
		//delete temp;
	}
}

//fenetre qui reste ouverte tant qu�elle n�est pas ferm�e
void gameState::handleInput()
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

	//permet de mettre a 0 les mouvements hors du polling
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
}
//aucune update
void gameState::update(float dt)
{
	//si ce n est pas gameOver
	if (_gameState != gameStates::gameOver) {
		//rajouter un if qui dit a l'ennemie de se diriger vers le player si il est dans le range
	}
	//si c�est playing, on a clique, donc on joue.

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


	for (int i = 0; i < _map->getWalls().size(); i++) {

	
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

		for (int j = 0; j < _ennemis.size(); j++)
		{
			if (_collision.checkSpriteCollision(_ennemis[j]->getSprite(), 0.6f, _map->getWalls().at(i), 1)) {

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
					_ennemis[j]->moveDown(dt);
				}

				else if (_collidingWallID == 7)
					_ennemis[j]->moveRight(dt);
				else if (_collidingWallID == 6)
					_ennemis[j]->moveLeft(dt);
				else
					_ennemis[j]->moveUp(dt);

				_ennemis[j]->setMove(false);
			}
			else if (i == 0) {
				_ennemis[j]->setMove(true);

			}
		}
		
	}

	if (_player->getY() > 150)		//fait en sorte que le background ne descende pas lorsque le joueur est bas dans la map
		_background.setPosition(_player->getX(), 150);
	else
	_background.setPosition(_player->getVectPosition());


	_hud->updateVie(_player->getVie());
	_hud->setPosition(Vector2f(_player->getX() +75, _player->getY() +54));

	for (int i = 0; i < _ennemis.size(); i++)
	{
		_ennemis[i]->update(dt, _player->getVectPosition());

		std::cout << "enemi no :" << i << ": " << _ennemis[i]->getVectPosition().x << "xay : " << _ennemis[i]->getVectPosition().y << std::endl;
	}
	
	

	//-------JUSQU'ICI---------------------------------------------------
}

//clear, dessine le background et display la fenetre. (dt neest pas utilise ici)
void gameState::draw(float dt) const
{
	_data->window.clear();	//nettoie la fenetre
	_data->window.setView(_viewJoueur);
	_data->window.draw(_background);
	_map->draw();

	for (int i = 0; i < _ennemis.size(); i++)
	{
		_data->window.draw(_ennemis[i]->getSprite());
	}
	
	_player->draw();
	_hud->draw();
	
	_data->window.display();	//affiche la frame
}