#pragma once
#include <Siv3D.hpp>


struct Scope
{
public:
	Scope() {
		
	}
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

/*
struct Mob
{
public:
	Mob() {

	}
	Mob(Vec2 p) {
		place = p;
		moveCount = 0;
		vec = Vec2(0, 0);
	}
	//void setRadius(int r) { radius = r; }

	void setPlace(Vec2 p) { place = p; }

	void Move(int M) {	//移動を完了する
		constexpr int MOVE_COUNT = 50;
		bool isReCalc = false;
		place += vec;
		//もし画面外に出ているならば
		if (place.x <= 280 || place.x >= 1600 || place.y <= 50 || place.y >= 900) {
			place -= vec;
			isReCalc = true;
		}
		else if (moveCount % MOVE_COUNT == 0) {
			isReCalc = true;
		}


		if (isReCalc) {
			do {
				deg = Random(0, 360) * Math::Pi / 180.0;
				vec.x = M * cos(deg);
				vec.y = M * sin(deg);
			} while (place.x + vec.x <= 280 || place.x + vec.x >= 1600 || place.y + vec.y <= 50 || place.y + vec.y >= 900);
		}
		moveCount++;
	}
	Vec2 getPlace(void) { return place; }
	bool deleteCheck(void) { return((place.x < 20) || (place.x > 660) || (place.y > 500)); }//後々変える

private:
	int radius;
	Vec2 place;
	Vec2 movement;
	float deg;
	int moveCount;
	Vec2 vec;
};


struct Target
{
public:
	Target() {

	}

	Target(int r, Vec2 p) {
		radius = r; place = p;
		moveCount = 0;
		vec = Vec2(0, 0);
	}

	void setRadius(int r) { radius = r; }
	void setPlace(Vec2 p) { place = p; }
	void Move(int M) {	//移動を完了する
		if(hit==false){
			constexpr int MOVE_COUNT = 20;
			bool isReCalc = false;
			place += vec;

			//もし画面外に出ているならば
			if (place.x <= 280 || place.x >= 1600 || place.y <= 50 || place.y >= 900) {
				place -= vec;
				isReCalc = true;
			}
			else if (moveCount % MOVE_COUNT == 0) {
				isReCalc = true;
			}

			if (isReCalc) {
				do {
					deg = Random(0, 360) * Math::Pi / 180.0;
					vec.x = M * cos(deg);
					vec.y = M * sin(deg);
				} while (place.x + vec.x <= 280 || place.x + vec.x >= 1600 || place.y + vec.y <= 50 || place.y + vec.y >= 900);
			}
			moveCount++;
		}
	}

	int getRadius(void) { return radius; }
	Vec2 getPlace(void) { return place; }
	bool deleteCheck(void) { return((place.x < 20) || (place.x > 660) || (place.y > 500)); }//後々変える

private:
	int radius;
	Vec2 place;
	float deg;
	int moveCount;
	Vec2 vec;	//移動量格納用
	bool hit=false;
};
*/
