#include "Shoe.h"

Shoe::Shoe(Array<bool>* hasItems) {
	this->hasItems = hasItems;
	isRotation = false;
	angle = 0;
	angleSpeed = 4;
	totalShoeVec = Vec2(0, GROUND - 80);
	gravity = 0.7;
	isFly = false;


	if (hasItems->at((int)GACHA_ITEM::SPORTS_SHOE)) {
		texture = new Texture(U"resources/images/items/game/shoekick/sportsshoe.png");
	}
	else {
		texture = new Texture(U"resources/images/items/game/shoekick/shoe.png");
	}

	//エフェクト初期化
	effects = new MyEffects();
	rocketEffect = new MyImageEffect(U"resources/images/items/game/shoekick/game/effects/rocket.png", 5, 4, 0.01);
	rocketCnt = 0;


}
Shoe::~Shoe() {
	delete texture;
}
void Shoe::setAngle(bool rotate) {
	isRotation = rotate;
}
bool Shoe::update() {
	if (isRotation) {
		angle += angleSpeed;
	}

	if (totalShoeVec.y >= GROUND) {//もし地面に着いているならば
		setAngle(false);//回転停止
		setGround();//座標を地面に修正
		if (shoeVec.x > 0) {//少し右に惰性で動かす
			shoeVec.x -= 5;
			totalShoeVec.x += shoeVec.x;
		}
		else {
			shoeVec.x = 0;
			return false;
		}
	}
	else {//飛んでいる最中
		updateRocket();
		setAngle(true);//回転開始
		totalShoeVec += shoeVec;//座標移動
		shoeVec.y += gravity / 2.0;
		if (shoeVec.y < 0) {//上昇中
			shoeVec.x -= 0.1;
		}
		else {//下降中
			shoeVec.x += 0.1;
		}
	}
	return true;
}
void Shoe::draw() {
	effects->draw();
	texture->rotated(ToRadians(angle)).draw(getShoePos());
}

Vec2 Shoe::getTotalVec() {
	return totalShoeVec;
}
void Shoe::setShoeVector(float kickPower) {
	constexpr float X_WEIGHT = 2.0, Y_WEIGHT = 4.0;
	constexpr Vec2 SPORTS_SHOE_WEIGHT = Vec2(1.5, 1.5);
	shoeVec = Vec2(kickPower / X_WEIGHT, -(kickPower / Y_WEIGHT));
	if (hasItems->at((int)GACHA_ITEM::SPORTS_SHOE)) {
		shoeVec *= SPORTS_SHOE_WEIGHT;
	}

}
void Shoe::setGround() {
	totalShoeVec.y = GROUND;
}

void Shoe::setFly(bool fly) {
	isFly = fly;
}
bool Shoe::isFlying() {
	return isFly;
}

Vec2 Shoe::getShoePos() {
	return Vec2(Window::ClientWidth() / 2, totalShoeVec.y + 20);
}

void Shoe::updateRocket() {
	constexpr Vec2 rocketVec(0.3, -2);
	rocketCnt++;
	if (hasItems->at((int)GACHA_ITEM::SPORTS_SHOE)) {

		if (rocketCnt >= 10 && rocketCnt <= 60 * 1.5) {
			if (rocketCnt <= 30) {
				shoeVec += rocketVec;
			}
			effects->add(rocketEffect, getShoePos());
		}
		
	}
}