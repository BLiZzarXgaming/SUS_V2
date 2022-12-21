#include "statsState.h"

//le constructeur utilise les : pour initialiser _data avant meme l execution du contenu
statsState::statsState(gameDataRef data) : _data(data)
{
}
//load l image du background a l aide du assetManager ds _data et la set au Sprite
void statsState::init()
{
	_data->assets.loadTexture("comment jouer state background", MAIN_MENU_STATE_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("comment jouer state background"));
	_background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);
	_background.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	_background.setScale(5, 5);

	// pour les textes
}
//fenetre qui reste ouverte tant qu elle n est pas fermee
void statsState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
		else if (event.type == Event::KeyPressed) {

			switch (event.key.code)
			{
			case Keyboard::Escape:
				_data->machine.addState(stateRef(new mainMenuState(_data)));
				break;
			}
		}
	}
}

// update le state (pas utilise)
void statsState::update(float dt)
{
}
//clear, dessine le background et display la fenetre. (dt n est pas utilise ici)
void statsState::draw(float dt) const
{
	_data->window.clear();
	_data->window.draw(_background);

	_data->window.display();
}