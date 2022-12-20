#include "Hud.h"

Hud::Hud(gameDataRef data) : _data(data)
{
	if (!_texture.loadFromFile("ressources/images/SUS_HealthBar_Sheet.png"))
	{
		//cout << "Le fichier de la texture du Hud est introuvable!";
	}

	_spriteVie.setTexture(_data->assets.getTexture("player healthbar"));
	_spriteVie.setScale(2, 2);
	_rectVie = IntRect(0, 0, 128, 16);
	_spriteVie.setTextureRect(_rectVie);

	if (!_font.loadFromFile("ressources/fonts/Robota-NonCommercial.otf"))
	{
		//cout << "Le fichier de police d'ecriture est introuvable!";
	}

	_nbBalle.setFont(_font);
	_nbBalle.setFillColor(Color::White);
	_nbBalle.setOutlineColor(Color::Black);
	_nbBalle.setOutlineThickness(1);
	_nbBalle.setCharacterSize(20);
	_nbBalle.setString("BALLE: 0");

	_spriteVie.setPosition(0, 0);
}

void Hud::setBalle(int nbBalle)
{
	_nbBalle.setString("BALLES: " + to_string(nbBalle));
}

void Hud::updateVie(int vie)
{
	_rectVie.top = (3 - vie) * 16;
	_spriteVie.setTextureRect(_rectVie);
}

void Hud::setPosition(sf::Vector2f position)
{
	_spriteVie.setPosition(position.x - 260, position.y - 160);
	_nbBalle.setPosition(position.x - 260, position.y - 150);

}

void Hud::draw() const
{
	_data->window.draw(_spriteVie);
	_data->window.draw(_nbBalle);
}
