#include "mainMenuState.h"

//le constructeur utilise les : pour initialiser _data avant meme l execution du contenu
mainMenuState::mainMenuState(gameDataRef data) : _data(data)
{
}
//load l image du background a l aide du assetManager ds _data et la set au Sprite
void mainMenuState::init()
{
	_data->assets.loadTexture("main menu state background", MAIN_MENU_STATE_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("main menu state background"));

	_data->assets.loadFont("font button", "TODO");

	// set les bouttons
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4), "UN JOUEUR");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 100), "COOP (SINGLE V2)"); // le mode coop pas possible
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 215), "STATS");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 315), "CREDITS");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 415), "COMMENT JOUER");
	setBoutton(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 515), "QUITTER");
}
//fenetre qui reste ouverte tant qu elle n est pas fermee
void mainMenuState::handleInput()
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
				_data->window.close();
				break;

			case Keyboard::Up:

				//_menuSound.play();
				moveUp();
				break;
			case Keyboard::Down:
				
				//_menuSound.play();
				moveDown();
				break;

			case Keyboard::Enter:				//TODO mettre les bon states
					switch (getBouttonChoisi()) // prend l'index du boutton choisi
					{
					case 0: //solo
						//_etatActuel = PLAY;
						break;
					case 1: // coop
						//_etatActuel = PLAY;
						break;
					case 2: // stats
						//_etatActuel = STATS;

						break;
					case 3: //credit
						//_etatActuel = CREDITS;
						break;
					case 4: // comment jouer
						//_etatActuel = COMMENT_JOUER;
						break;
					case 5: // quitter
						//_etatActuel = QUITTER;
						break;
					}
				break;
			}
		}
		else if (_data->input.isSpriteClicked(_playButton, Mouse::Left, _data->window)) {
			//create the new state main screen
			//_data->machine.addState(stateRef(new gameState(_data)), true);
			cout << "go to game state" << endl;
		}
	}
}

void mainMenuState::update(float dt)
{
	for (int i = 0; i < _boutton.size(); i++)
	{
		if (i == _bouttonActuel)
		{
			_boutton[_bouttonActuel].setFillColor(COLOR_ACTUAL_BUTTON);
		}
		else
		{
			_boutton[i].setFillColor(COLOR_BUTTON);
		}
	}
	//todo call the menu state
	//_data->machine.addState(stateRef(new gameState(_data)), true);
	std::cout << "in the main menu" << endl;
}
//clear, dessine le background et display la fenetre. (dt n est pas utilise ici)
void mainMenuState::draw(float dt)
{
	_data->window.draw(_background);

	for (int i = 0; i < _boutton.size(); i++)
	{
		_data->window.draw(_boutton[i]);
	}
}

void mainMenuState::moveDown()
{
	if (_bouttonActuel < _boutton.size() - 1)
	{
		_bouttonActuel++;
	}
	else
	{
		_bouttonActuel = 0;
	}
	std::cout << "boutton actuel " << _bouttonActuel << std::endl;
}

void mainMenuState::moveUp()
{
	if (_bouttonActuel > 0)
	{
		_bouttonActuel--;
	}
	else
	{
		_bouttonActuel = _boutton.size() - 1;
	}
	std::cout << "boutton actuel " << _bouttonActuel << std::endl;
}

int mainMenuState::getBouttonChoisi()
{
	return _bouttonActuel;
}

void mainMenuState::setBoutton(sf::Vector2f position, std::string message)
{
	Text text; // le texte du boutton
	text.setString(message);
	text.setFillColor(COLOR_TEXT);
	text.setCharacterSize(SIZE_CARACTER_MENU);
	text.setFont(_data->assets.getFont("font button"));
	text.setOutlineColor(Color::White);
	text.setOutlineThickness(4);
	text.setPosition(position.x - text.getGlobalBounds().width / 2, position.y); // permet de centrer le boutton horizontalement
	_texts.push_back(text);

	RectangleShape rectangle; // le rectangle du boutton
	rectangle.setSize(Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));
	rectangle.setPosition(position.x - text.getGlobalBounds().width / 2 - 10, position.y + 10);

	std::cout << text.getGlobalBounds().width << std::endl;
	rectangle.setFillColor(COLOR_BUTTON);
	_boutton.push_back(rectangle);

}