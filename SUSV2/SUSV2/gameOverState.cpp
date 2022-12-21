#include "gameOverState.h"
gameOverState::gameOverState(gameDataRef data, int score) : _data(data), _score(score)
{
	_score = score;
	cout << _score;
}

void gameOverState::init()
{
}

void gameOverState::handleInput()
{
}

void gameOverState::update(float dt)
{
}

void gameOverState::draw(float dt) const
{
}