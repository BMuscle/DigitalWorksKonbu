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

	Vec2 getMovement(int M) {
		P = place;
		do {
			place = P;
			deg = Random(0, 360) * Math::Pi / 180.0;
			place.x = M * cos(deg);
			place.y = M * sin(deg);
			place = P + place;
		} while (place.x <= 280 || place.x >= 1600 || place.y <= 50 || place.y >= 900);
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


	Vec2 getMovement(int M) {
		P = place;
		do {
			place = P;
			deg = Random(0, 360) * Math::Pi / 180.0;
			place.x = M * cos(deg);
			place.y = M * sin(deg);
			place = P + place;
		} while (place.x <= 280 || place.x>=1600 || place.y <=50 || place.y>=900);
		return Vec2(place);
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