#include "fade.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
fade::fade(gameDataRef data) : _data(data) {
	_shape = RectangleShape(Vector2f(_data->window.getSize())); //même size que window
	_shape.setFillColor(Color(0, 0, 0, 0)); //set à blanc, transparent
	_flashOn = true;
}

/*Pour faire le flash screen, on joue avec la transparence d’un rectangle blanc aussi grand
que la fenêtre. Quand alpha est à 0, c’est transparent et quand il est à 255, il est blanc
opaque. On utilise le speed pour augmenter l’opacité jusqu’au blanc et le redescendre jusqu’à
transparent, ce qui crée l’effet d’un flash*/
void fade::show(float dt)
{
	int alpha;
if (_flashOn) { //commence le flash jusqu’à l’opacité 255
		alpha = (int)_shape.getFillColor().a + (FADE_SPEED * dt);
		if (alpha  >= 255.0f) {
			alpha = 255.0f;
			_flashOn = false; //set off le flash
		}
	}
	else { //diminue l’opacité pour revenir à 0, transparence
		alpha = (int)_shape.getFillColor().a - (FADE_SPEED * dt);
		if (alpha <= 0.0f) {
			alpha = 0.0f;
		}
	}
	_shape.setFillColor(Color(255, 255, 255, alpha));
}
void fade::draw() {
	_data->window.draw(_shape);
}