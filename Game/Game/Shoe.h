#pragma once
#include <Siv3D.hpp>
#include "ShoeKickGame.h"
#include "MyImageEffect.h"
#include "MyEffects.h"
class Shoe {
private:
	
	Array<bool> *hasItems;//取得しているアイテム

	bool isFly;			//飛んでいるかフラグ
	bool isRotation;	//回転フラグ
	float angle;		//回転量
	float angleSpeed;	//回転スピード
	Texture* texture;

	Vec2 shoeVecInit;	//靴飛ばしベクトル初期値
	Vec2 shoeVec;		//靴飛ばしベクトル
	Vec2 totalShoeVec;	//総移動距離
	float gravity;		//重力

	MyEffects* effects;
	MyImageEffect* rocketEffect;
	MyImageEffect* angelEffect;

	int rocketCnt;
	int angelCnt;
	void updateRocket();
	void updateAngel();

	Vec2 getShoePos();

public:
	Shoe(Array<bool> *hasItems);
	~Shoe();
	void setAngle(bool rotate);
	bool update();
	void draw();

	Vec2 getTotalVec();

	void setShoeVector(float kickPower);

	void setGround();

	void setFly(bool fly);
	bool isFlying();
};