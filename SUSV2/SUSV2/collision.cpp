#include "collision.h"

bool collision::checkSpriteCollision(Sprite sprite1, Sprite sprite2) const
{
	Rect<float> rect1 = sprite1.getGlobalBounds(); //on crée un rectangle des
	Rect<float> rect2 = sprite2.getGlobalBounds(); //dimensions des sprites reçus
	return rect1.intersects(rect2); //true, ils entrent en contact, false sinon
}