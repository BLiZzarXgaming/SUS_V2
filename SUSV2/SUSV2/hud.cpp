/********************************************************************************************/
/* Auteur      : Xavier Caouette                                                            */
/* Nom         : hud.cpp																	*/
/* Date        : 21 decembre 2022                                                           */
/* But         : Objet qui donne des informations sur la vie et le nombre de balle sur un   */
/*               ecran                                                                      */
/********************************************************************************************/

#include "Hud.h"

// construit les objet sprite et text du HUD
Hud::Hud(gameDataRef data) : _data(data)
{
	
	// pour la barre de vie
	_spriteVie.setTexture(_data->assets.getTexture("player healthbar"));
	_spriteVie.setScale(2, 2);
	_rectVie = IntRect(0, 0, 128, 16);
	_spriteVie.setTextureRect(_rectVie);
	_spriteVie.setPosition(0, 30);

	// pour le texte nombre de balle
	_nbBalle.setFont(_data->assets.getFont("font button"));
	_nbBalle.setFillColor(Color::White);
	_nbBalle.setOutlineColor(Color::Black);
	_nbBalle.setOutlineThickness(1);
	_nbBalle.setCharacterSize(20);
	_nbBalle.setString("BALLE: 0");
	_nbBalle.setPosition(0, 60);
}

// modifie le string du text nbr de balle
void Hud::setBalle(int nbBalle)
{
	_nbBalle.setString("BALLES: " + to_string(nbBalle));
}

// modifie la vie du joueur
void Hud::updateVie(int vie)
{
	_rectVie.top = (3 - vie) * 16;
	_spriteVie.setTextureRect(_rectVie);
}

// place la barre de vie et le nombre de balle dans la fenetre
void Hud::setPosition(sf::Vector2f position)
{
	_spriteVie.setPosition(position.x - 260, position.y - 160);
	_nbBalle.setPosition(position.x - 260, position.y - 150);

}

// Dessine la barre de vie et le nombre de balle
void Hud::draw() const
{
	_data->window.draw(_spriteVie);
	_data->window.draw(_nbBalle);
}
