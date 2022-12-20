#pragma once

#include <SFML/Graphics.hpp>
#include "game.h"
#include "state.hpp"

class Hud {
private:
	gameDataRef _data;
	// Sprite
	sf::Texture _texture;
	sf::Sprite _spriteVie;
	sf::IntRect _rectVie;

	// Texte
	sf::Text _nbBalle;
	sf::Font _font;

public:
	Hud(gameDataRef data);
	void setBalle(int);
	void updateVie(int);

	void setPosition(sf::Vector2f position);
	void draw() const;

};