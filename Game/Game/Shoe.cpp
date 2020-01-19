#include "Shoe.h"

Shoe::Shoe() {
	isRotation = false;
	angle = 0;
	angleSpeed = 4;
	texture = new Texture(U"resources/images/items/game/shoekick/shoe.png");
}
Shoe::~Shoe() {
	delete texture;
}
void Shoe::setAngle(bool rotate) {
	isRotation = rotate;
}
void Shoe::update() {
	if (isRotation) {
		angle += angleSpeed;
	}
}
void Shoe::draw(Vec2 pos) {
	texture->rotated(ToRadians(angle)).draw(pos.x, pos.y + 20);
}