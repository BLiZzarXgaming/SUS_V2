#include "gameWinState.h"
gameWinState::gameWinState(gameDataRef data, int score) : _data(data), _score(score)
{
	_score = score;
	cout << _score;
}

void gameWinState::init()
{
}

void gameWinState::handleInput()
{
}

void gameWinState::update(float dt)
{
}

void gameWinState::draw(float dt) const
{
}
