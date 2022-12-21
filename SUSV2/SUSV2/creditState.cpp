/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : creditState.cpp                                                            */
/* Date        : 21 decembre 2022                                                           */
/* But         : afficher les credit et reveien au menu apres                               */
/********************************************************************************************/
#include "creditState.h"

//le constructeur utilise les : pour initialiser _data avant meme l execution du contenu
creditState::creditState(gameDataRef data) : _data(data)
{
}

// initialise le state
void creditState::init()
{
	// load l'image
	_data->assets.loadTexture("comment jouer state background", CREDIT_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("comment jouer state background"));

	// place le sprite dans la fenetre
	_background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);
	_background.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	_background.setScale(5, 5);
}

// gere les entrees
void creditState::handleInput()
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

// update le state (pas utilise)
void creditState::update(float dt)
{
}
//clear, dessine le background et display la fenetre. (dt n est pas utilise ici)
void creditState::draw(float dt) const
{
	_data->window.clear();
	_data->window.draw(_background);

	_data->window.display();
}