#pragma once
#include"DodgeSceneBase.h"
#include<Siv3D.hpp>
#include<math.h>

enum STAGE {
	START,
	RULE,
	GAME,
	STOP,
};

class DodgeGame :public DodgeSceneBase
{
public:
	DodgeGame(DODGE_SCENE* nextScene);
	~DodgeGame();
	void start(void);
	void update();
	void draw();
private:
	void Match();
	bool HitCheck(int r1,Vec2 z1,int r2,Vec2 z2);
	Audio* backAudio;
	STAGE nowselect;
	int flag=1;
};

struct Scope
{
public:
	Scope(int r, Vec2 p) {
		radius = r; place = p;
	}
	void setRadius(int r) { radius = r; }
	void setPlace(Vec2 p) { place = p; }
	int getRadius(void) { return radius; }
	Vec2 getPlace(void) { return place; }
	bool deleteCheck(void) { return((place.x < 20) || (place.x > 660) || (place.y > 500)); }//画面サイズ？
private:
	int radius;
	Vec2 place;
	//int color;

};

struct Mob
{
public:
	Mob( Vec2 p) {
		 place = p;
	}
	//void setRadius(int r) { radius = r; }
				
	void setPlace(Vec2 p) { place = p; }

	Vec2 Getmovement(Vec2 p, int M) {
		P = p;
		deg = Random(0, 360) * Math::Pi / 180.0;
		p.x = M * cos(deg);
		p.y = M * sin(deg);
		place = P + p;
		return Vec2(place);
	}
	Vec2 getPlace(void) { return place; }
	bool deleteCheck(void) { return((place.x < 20) || (place.x > 660) || (place.y > 500)); }//後々変える
private:
	int radius;
	Vec2 place;
	Vec2 movement;
	float deg;
	Vec2 P;
};

struct Target
{
public:
	Target(int r, Vec2 p) {
		radius = r; place = p;
	}
	void setRadius(int r) { radius = r; }
	void setPlace(Vec2 p) { place = p; }

	Vec2 Getmovement(Vec2 p, int M) {
		P = p;
		deg = Random(0, 360) * Math::Pi / 180.0;
		p.x = M * cos(deg);
		p.y = M * sin(deg);
		place = P + p;
		return Vec2 (place);
	}
	int getRadius(void) { return radius; }
	Vec2 getPlace(void) { return place; }
	bool deleteCheck(void) { return((place.x < 20) || (place.x > 660) || (place.y > 500)); }//後々変える
private:
	int radius;
	Vec2 place;
	Vec2 P;
	float deg;


};
//Vec2って何？
//座標感覚
//