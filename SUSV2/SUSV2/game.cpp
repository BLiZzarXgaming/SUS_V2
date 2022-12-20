#include "game.h"
#include "splashState.h" //enlever le commentaire lors de l�appel du spashState
// � enlever apr�s
//#include "mainMenuState.h"
//#include "gameState.h"
#include <time.h>
#include <stdlib.h>


game::game(int width, int height, string title)
{
	_data = make_shared<gameData>(); //cr�ation de la game en m�moire dynamique

	//creation de la fenetre qui changera de contenu selon la state creee ensuite
	_data->window.create(VideoMode(width, height), title, Style::Fullscreen | Style::Close);
	_data->window.setFramerateLimit(60);
	
	//todo cr�ation d�un 1er �tat de jeu (1�re fen�tre)
	_data->machine.addState(stateRef(new splashState(_data)));

	run();
}
//le game loop de tout jeu fonctionne comme suit : on execute a� chaque loop la methode
//processStateChanges qui verifie si on ajoute, on modifie ou on retire une state pour ensuite
//ajuster le temps passe et executer des traitements particuliers a� chaque (1/60sec)
//ces traitements sont gerer par la state machine. Ensuite, on dessine les changements
void game::run()
{
	float newTime, frameTime, interpolation;
	float currentTime = _clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	while (_data->window.isOpen())
	{
		_data->machine.processStateChanges(); //vérifie si on a des changements
		
		newTime = _clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f) {	//si on dépasse le quart de seconde, on ajuste
			frameTime = 0.25f;		//a .25 seconde pour le calcul de accumulator
		}
		currentTime = newTime;		 //new time devient le current time
		
		accumulator += frameTime;		//accumulator accumule tous les frameTimes
		
		while (accumulator >= dt) {		//si on depasse le temps du frame (1/60 de seconde)
										//on verifie les evenements et on update la fenetre
			_data->machine.getActiveState()->handleInput();
			_data->machine.getActiveState()->update(dt);
			accumulator -= dt;			//on retire dt de l accumulator pour l interpolation
		}
		interpolation = accumulator / dt; //le temps d execution de la loop pour le draw
		_data->machine.getActiveState()->draw(interpolation);
	}
}