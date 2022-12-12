#include "gameState.h"

gameState::gameState(gameDataRef data) : _data(data)
{
	_map = nullptr;
	_gameState = gameStates::ready;
}

gameState::~gameState()
{
	delete _map;
}

void gameState::init()
{
	_data->assets.loadTexture("mapTileSet", MAP_TILESET_FILEPATH);
	_data->assets.loadTexture("main background", MAIN_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("main background"));
	_background.setPosition(100, -20);
	
	_map = new gameMap(_data);
}

void gameState::handleInput()
{
}

void gameState::update(float dt)
{
}

void gameState::draw(float dt) const
{
	_data->window.clear();
	_data->window.draw(_background);
	_map->draw();
	_data->window.display();
}