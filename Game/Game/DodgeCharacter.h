#pragma once
#include <Siv3D.hpp>
#include<math.h>

#define AREA_LEFT 280 
#define AREA_RIGHT 1600 
#define AREA_UP 50 
#define AREA_DOWN 900 
#define DODGE_CHAR_CHIP_SIZE 3
constexpr int MOVE_COUNT = 50;

struct DodgeCharacter
{
public:
	DodgeCharacter() {

	}
	DodgeCharacter(Vec2 p, String filepath) {
		pos = p;
		moveCount = MOVE_COUNT;
		nowDir = CHAR_DIR::S;
		nowChip = 0;
		chipCnt = 0;
		vec = Vec2(0, 0);
		Image baseimage = Image(filepath);
		float chipW=baseimage.width()/ DODGE_CHAR_CHIP_SIZE;
		float chipH= baseimage.height() / (int)CHAR_DIR::SIZE;
		for (int dir = 0; dir < (int)CHAR_DIR::SIZE; dir++) {
			for (int i = 0; i < DODGE_CHAR_CHIP_SIZE; i++) {
				charChip[dir][i] = new Texture(baseimage.clipped(chipW * i, chipH * dir, chipW, chipH));
			}
		}
	}

	void Move(int M) {	//移動を完了する
		if (chipCnt == 15) {
			chipCnt = 0;
			nowChip++;
			if (nowChip >= DODGE_CHAR_CHIP_SIZE)nowChip = 0;
		}
		//次の座標が画面外だった場合の座標計算
		if (isOut(pos + vec) || moveCount  >=MOVE_COUNT) {
			int angle;
			do {
				moveCount = 0;
				angle = Random(0, 360);
				vec.x = M * cos(angle * Math::Pi / 180.0);
				vec.y = M * sin(angle * Math::Pi / 180.0);
			} while (isOut(pos+vec));
			nowDir= calcDir(angle);
		}
		pos += vec;
		moveCount++;
		chipCnt++;
	}

	void setPlace(Vec2 p) { pos = p; } //現在地の保持
	Vec2 getPlace(void) { return pos; } 
	//target当たり判定用半径
	float getRadius() {
		int length;
		if (charChip[0][0]->width() > charChip[0][0]->height())length = charChip[0][0]->height();
		else length = charChip[0][0]->width();
		return length / 2;
	}
	//bool deleteCheck(void) { return((pos.x < 20) || (pos.x > 660) || (pos.y > 500)); }//後々変える
	//画面外判定
	bool isOut(Vec2 pos) {
		if (pos.x <= AREA_LEFT || pos.x >= AREA_RIGHT || pos.y <= AREA_UP || pos.y >= AREA_DOWN) {
			return true;
		}
		return false;
	}
	//描画
	void draw() {
		charChip[(int)nowDir][nowChip]->drawAt(pos);
	}

private:
	enum class CHAR_DIR {
		S,
		W,
		E,
		N,
		SIZE,
	};
	CHAR_DIR calcDir(int angle) {
		if (angle < 45 || 315 <= angle)return CHAR_DIR::E;
		else if (angle < 135)return CHAR_DIR::S;
		else if (angle < 225)return CHAR_DIR::W;
		else
			return CHAR_DIR::N;
	}
	CHAR_DIR nowDir;//現在の方向
	int nowChip;
	int chipCnt;
	int radius;//Target用当たり判定半径
	int moveCount;//同じ方向に動いた回数
	Vec2 pos;	//位置
	Vec2 vec;

	Texture* charChip[(int)CHAR_DIR::SIZE][DODGE_CHAR_CHIP_SIZE];
	
};

