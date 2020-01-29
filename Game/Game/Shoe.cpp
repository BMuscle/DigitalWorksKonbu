#include "Shoe.h"

#define SHOE_INIT_Y GROUND - 80
Shoe::Shoe(Array<bool>* hasItems) {
	this->hasItems = hasItems;
	isRotation = false;
	angle = 0;
	angleSpeed = 4;
	totalShoeVec = Vec2(0, SHOE_INIT_Y);
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
	rocketEffect = new MyImageEffect(U"resources/images/items/game/shoekick/game/effects/rocket.png", 8, 1, 0.01, -120);
	rocketCnt = 0;

	angelEffect = new MyImageEffect(U"resources/images/items/game/shoekick/game/effects/angel.png", 5, 3, 0.02);
	angelCnt = 0;

	AudioAsset::Register(U"explosion", U"resources/musics/items/game/shoekick/explosion.wav");
	AudioAsset::Register(U"pop", U"resources/musics/items/game/shoekick/pop.wav");
	AudioAsset::Register(U"kira", U"resources/musics/items/game/shoekick/kira.wav");
	AudioAsset::Register(U"slide", U"resources/musics/items/game/shoekick/slide.wav");
	AudioAsset::Register(U"roll", U"resources/musics/items/game/shoekick/roll.wav");

}
Shoe::~Shoe() {
	delete texture;
	delete effects;
	delete rocketEffect;
	delete angelEffect;
	AudioAsset::Unregister(U"explosion");
	AudioAsset::Unregister(U"pop");
	AudioAsset::Unregister(U"kira");
	AudioAsset::Unregister(U"slide");
	AudioAsset::Unregister(U"roll");
}
void Shoe::setAngle(bool rotate) {
	isRotation = rotate;
}
bool Shoe::update() {
	if (isRotation) {
		angle += angleSpeed;
	}

	if (totalShoeVec.y >= GROUND) {//もし地面に着いているならば
		if ((int)angle % 180 <= 10) {
			setAngle(false);//回転停止
		}
		setGround();//座標を地面に修正
		if (shoeVec.x > 0) {//少し右に惰性で動かす
			if (hasItems->at((int)GACHA_ITEM::ROLLER)) {//ローラーの場合摩擦を緩くする
				shoeVec.x -= 0.1;
				/*
				AudioAsset(U"roll").setVolume(0.3);
				AudioAsset(U"roll").play();
				*/
				AudioAsset(U"slide").setVolume(0.3);
				AudioAsset(U"slide").setSpeed(0.2);
				AudioAsset(U"slide").play();
			}
			else {
				shoeVec.x -= 5;
				AudioAsset(U"slide").setVolume(0.3);
				AudioAsset(U"slide").play();
			}
			totalShoeVec.x += shoeVec.x;
		}
		else {
			shoeVec.x = 0;
			AudioAsset(U"roll").stop();
			AudioAsset(U"slide").stop();
			return false;
		}
	}
	else {//飛んでいる最中
		updateRocket();
		updateAngel();
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
	constexpr float KICKWEIGHT = 3;
	kickPower *= KICKWEIGHT;
	constexpr float X_WEIGHT = 5.0, Y_WEIGHT = 13.0;
	constexpr Vec2 SPORTS_SHOE_WEIGHT = Vec2(1.2, 1.2);
	shoeVec = Vec2(kickPower / X_WEIGHT, -(kickPower / Y_WEIGHT));
	if (hasItems->at((int)GACHA_ITEM::SPORTS_SHOE)) {
		shoeVec *= SPORTS_SHOE_WEIGHT;
	}
	shoeVecInit = shoeVec;
}
void Shoe::setGround() {
	totalShoeVec.y = GROUND;
}

void Shoe::setFly(bool fly) {
	isFly = fly;
	if (fly) {
		AudioAsset(U"pop").setPosSec(0);
		AudioAsset(U"pop").setVolume(0.3);
		AudioAsset(U"pop").play();
	}
}
bool Shoe::isFlying() {
	return isFly;
}

Vec2 Shoe::getShoePos() {
	return Vec2(Scene::Width() / 2, totalShoeVec.y + 20);
}

void Shoe::updateRocket() {
	constexpr Vec2 rocketVec(0.2, -0.3);
	
	if (hasItems->at((int)GACHA_ITEM::ROCKET_BOOSTER)) {
		if (rocketCnt == 0) {
			AudioAsset(U"explosion").setPosSec(0);
			AudioAsset(U"explosion").setVolume(0.3);
			AudioAsset(U"explosion").play();
		}
		if (rocketCnt >= 10) {
			if (rocketCnt <= 30) {
				shoeVec += rocketVec;
			}
			if (rocketCnt % 3 == 0) {
				effects->add(rocketEffect, getShoePos() + Vec2(-30,90));
			}
		}
	}
	rocketCnt++;
}

void Shoe::updateAngel() {

	if (hasItems->at((int)GACHA_ITEM::WING)) {
		if (angelCnt == 0) {
			if (SHOE_INIT_Y < totalShoeVec.y) {
				angelCnt++;//２段ジャンプ開始
				shoeVec = shoeVecInit / 1.5;
				AudioAsset(U"kira").setPosSec(0);
				AudioAsset(U"kira").setVolume(0.3);
				AudioAsset(U"kira").play();
			}
		}
		else if(angelCnt <= 30){
			angelCnt++;
			effects->add(angelEffect, getShoePos());
		}

	}

}