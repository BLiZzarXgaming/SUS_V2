/********************************************************************************************/
/* Auteur      : Louis-Philippe Racette                                                     */
/* Nom         : mainMenuState.cpp                                                          */
/* Date        : 21 decembre 2022                                                           */
/* But         : Affiche un menu avec des bouttons pour changer de state                    */
/********************************************************************************************/

#include "mainMenuState.h"

//le constructeur utilise les : pour initialiser _data avant meme l execution du contenu
mainMenuState::mainMenuState(gameDataRef data) : _data(data)
{
	// alloue d avance l espace necessaire
	_boutton.reserve(6);
	_texts.reserve(6);
}

//load l image du background a l aide du assetManager ds _data, la set au Sprite et fait les bouttons
void mainMenuState::init()
{
	// pour le background
	_data->assets.loadTexture("main menu state background", MAIN_MENU_STATE_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("main menu state background"));
	_background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);
	_background.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	_background.setScale(5, 5);

	// pour les textes
	_data->assets.loadFont("font button", MAIN_FONT_FILEPATH);
	

	// set les bouttons
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4), "UN JOUEUR");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 100), "COOP (SINGLE V2)"); // le mode coop si on a le temps
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 215), "STATS");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 315), "CREDITS");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 415), "COMMENT JOUER");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 515), "QUITTER");
}

// gere tout les inputs du menu
void mainMenuState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))	// regarde tout les evenements
	{
		if (event.type == Event::Closed)	// si on pese sur le x de la fenetre
			_data->window.close();
		else if (event.type == Event::KeyPressed) {	// tout les evenements de touche pese

			switch (event.key.code)					// regarde le type de touche
			{
			case Keyboard::Escape:					// touche escape
				_data->window.close();
				break;

			case Keyboard::Up:						// fleche haut

				//_menuSound.play();
				moveUp();
				break;
			case Keyboard::Down:					// fleche bas
				
				//_menuSound.play();
				moveDown();
				break;

			case Keyboard::Enter:					// touche enter
					switch (getBouttonChoisi())		// prend l'index du boutton choisi
					{
					case 0: //solo
						_data->machine.addState(stateRef(new gameState(_data)));
						break;
					case 1: // coop
						_data->machine.addState(stateRef(new gameState(_data)));
						break;
					case 2: // stats
						_data->machine.addState(stateRef(new statsState(_data)));
						break;
					case 3: //credit
						_data->machine.addState(stateRef(new creditState(_data)));
						break;
					case 4: // comment jouer
						_data->machine.addState(stateRef(new commentJouerState(_data)));
						break;
					case 5: // quitter
						_data->window.close();
						break;
					}
				break;
			}
		}
	}
}

// udpade les elements du menu
void mainMenuState::update(float dt)
{
	for (int i = 0; i < _boutton.size(); i++)	// boucle tout les bouttons
	{
		if (i == _bouttonActuel)				// si c'est le boutton choisi
		{
			_boutton[_bouttonActuel].setFillColor(COLOR_ACTUAL_BUTTON);
		}
		else
		{
			_boutton[i].setFillColor(COLOR_BUTTON);
		}
	}
}

//clear, dessine le background et display la fenetre. (dt n est pas utilise ici)
void mainMenuState::draw(float dt) const 
{
	_data->window.clear();
	_data->window.draw(_background);

	for (int i = 0; i < _boutton.size(); i++)
	{
		_data->window.draw(_boutton[i]);
		_data->window.draw(_texts[i]);
	}
	_data->window.display();
}

// bouge le boutton choisi de 1 en bas
void mainMenuState::moveDown()
{
	if (_bouttonActuel < _boutton.size() - 1)	// verifie si on depasse
	{
		_bouttonActuel++;
	}
	else
	{
		_bouttonActuel = 0;
	}
	std::cout << "boutton actuel " << _bouttonActuel << std::endl;
}

// bouge le boutton choisi de 1 en haut
void mainMenuState::moveUp()
{
	if (_bouttonActuel > 0)	// verifie si on depasse
	{
		_bouttonActuel--;
	}
	else
	{
		_bouttonActuel = _boutton.size() - 1;
	}
	std::cout << "boutton actuel " << _bouttonActuel << std::endl;
}

// donne l'index du boutton choisi
int mainMenuState::getBouttonChoisi()
{
	return _bouttonActuel;
}

// crée un boutton avec un text et un rectangle
void mainMenuState::setBoutton(sf::Vector2f position, std::string message)
{
	// le texte du boutton
	Text text; 
	text.setString(message);
	text.setFillColor(COLOR_TEXT);
	text.setCharacterSize(SIZE_CARACTER_MENU);
	text.setFont(_data->assets.getFont("font button"));
	text.setOutlineColor(Color::White);
	text.setOutlineThickness(4);
	text.setPosition(position.x - text.getGlobalBounds().width / 2, position.y); // permet de centrer le boutton horizontalement
	_texts.push_back(text);

	// le rectangle du boutton
	RectangleShape rectangle; 
	rectangle.setSize(Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));
	rectangle.setPosition(position.x - text.getGlobalBounds().width / 2 - 10, position.y + 10);	// permet de centrer le boutton horizontalement
	rectangle.setFillColor(COLOR_BUTTON);
	_boutton.push_back(rectangle);

}