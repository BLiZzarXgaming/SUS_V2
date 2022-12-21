#include "fade.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
fade::fade(gameDataRef data) : _data(data) {
	_shape = RectangleShape(Vector2f(_data->window.getSize())); //m�me size que window
	_shape.setFillColor(Color(0, 0, 0, 0)); //set � blanc, transparent
	_flashOn = true;
}

/*Pour faire le flash screen, on joue avec la transparence d�un rectangle blanc aussi grand
que la fen�tre. Quand alpha est � 0, c�est transparent et quand il est � 255, il est blanc
opaque. On utilise le speed pour augmenter l�opacit� jusqu�au blanc et le redescendre jusqu��
transparent, ce qui cr�e l�effet d�un flash*/
void fade::show(float dt)
{
	int alpha;
if (_flashOn) { //commence le flash jusqu�� l�opacit� 255
		alpha = (int)_shape.getFillColor().a + (FADE_SPEED * dt);
		if (alpha  >= 255.0f) {
			alpha = 255.0f;
			_flashOn = false; //set off le flash
		}
	}
	else { //diminue l�opacit� pour revenir � 0, transparence
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