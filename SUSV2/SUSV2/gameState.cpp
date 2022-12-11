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
	_map->draw();
	_data->window.display();
}