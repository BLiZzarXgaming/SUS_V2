#include "gameWinState.h"
gameWinState::gameWinState(gameDataRef data, int score)
{
	_score = score;
	cout << _score;
}

void gameWinState::init()
{
	_scoreText.setString("Victoire! Votre score :" + to_string(_score));
	_scoreText.setFillColor(COLOR_TEXT);
	_scoreText.setCharacterSize(SIZE_CARACTER_MENU);
	_scoreText.setFont(_data->assets.getFont("font button"));
	_scoreText.setOutlineColor(Color::White);
	_scoreText.setOutlineThickness(4);
	_scoreText.setPosition(SCREEN_WIDTH / 2 - _scoreText.getGlobalBounds().width / 2, SCREEN_HEIGHT / 4 + 215);

	_rectangle.setSize(Vector2f(_scoreText.getGlobalBounds().width + 20, _scoreText.getGlobalBounds().height + 20));
	_rectangle.setPosition(SCREEN_WIDTH / 2 - _scoreText.getGlobalBounds().width / 2 - 10, SCREEN_HEIGHT / 4 + 215 + 10);
	_rectangle.setFillColor(COLOR_BUTTON);
}

void gameWinState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))	// boucle les evenement
	{
		if (event.type == Event::Closed)	// si on pese sur le x
			_data->window.close();
		else if (event.type == Event::KeyPressed) {	// si on pese sur une touche

			switch (event.key.code)					// le nom de la touche
			{
			case Keyboard::Escape:					// si escape
				_data->machine.addState(stateRef(new mainMenuState(_data)));
				break;
			}
		}
	}
}

void gameWinState::update(float dt)
{
}

void gameWinState::draw(float dt) const
{
	_data->window.clear();
	_data->window.draw(_rectangle);
	_data->window.draw(_scoreText);

	_data->window.display();
}
