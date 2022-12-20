#include "splashState.h"
//le constructeur utilise les : pour initialiser _data avant meme l execution du contenu{}
splashState::splashState(gameDataRef data) : _data(data)
{
}
//load l image du background a l aide du assetManager ds _data et la set au Sprite
void splashState::init()
{
	_data->assets.loadTexture("logo state background", SPLASH_STATE_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("logo state background"));
	_background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);
	_background.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4);
	_background.setScale(2, 2);
}
//fenetre qui reste ouverte tant qu elle n est pas fermee
void splashState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
	}
}
//gere le delai, apres 3 secondes, on veut afficher la prochaine fenetre
void splashState::update(float dt)
{
	if (_clock.getElapsedTime().asSeconds() > LOGO_STATE_SHOW_TIME)
	{
		//todo call the menu state
		_data->machine.addState(stateRef(new mainMenuState(_data)), true);
		std::cout << "go to the main menu" << endl;
	}
}
//clear, dessine le background et display la fenetre. (dt n est pas utilise ici)
void splashState::draw(float dt) const
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.display();
}