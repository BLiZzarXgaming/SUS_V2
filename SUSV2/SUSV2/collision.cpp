#include "collision.h"

bool collision::checkSpriteCollision(Sprite sprite1, float scale1, Sprite sprite2, float scale2) const
{
	sprite1.setScale(scale1, scale1);
	sprite2.setScale(scale2, scale2);
	Rect<float> rect1 = sprite1.getGlobalBounds();
	Rect<float> rect2 = sprite2.getGlobalBounds();
	return rect1.intersects(rect2);
}