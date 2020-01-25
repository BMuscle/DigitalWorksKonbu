#pragma once
#include<Siv3D.hpp>
#include"DodgeSceneBase.h"
#include"MyKey.h"
#include"Dodge.h"
#include"MySceneManager.h"
#include"DodgeGame.h"
#include"MyEffects.h"
#include"MyImageEffect.h"

#define DODGE_PLAYER_ROW_SIZE 6
#define DODGE_PLAYER_LINE_SIZE 4
#define ALL_MOTION 7
//player表示用添え字
constexpr Vec2 A = Vec2(2, 0);
constexpr Vec2 B = Vec2(2, 2);
constexpr Vec2 C = Vec2(2, 0);
constexpr Vec2 D = Vec2(1, 4);
constexpr Vec2 E = Vec2(1, 3);
constexpr Vec2 F = Vec2(1, 3);
constexpr Vec2 END = Vec2(1, 3);


class DodgeHitMotion :public DodgeSceneBase {
public:
	DodgeHitMotion(DODGE_SCENE* nextScene, int ballCnt,float dVelocity,int hitLevel,struct Score score);
	~DodgeHitMotion();
	void start(void);
	void update();
	void draw();
	int getBallCnt();			//引数用関数
	struct Score getScore();	//引数用関数

private:
	//引数
	int ballCnt;
	float dVelocity;
	int hitLevel;
	struct Score score;

	enum SPEED {
		FAST = 90,
		NORMAL = 50,
		LATE = 20,
	};
	enum MODE {
		ANIME,
		JUDGE,
		NEXT,
	};
	enum STATE {
		NONE,
		HIT,
		MISS,
	};

	class MyEffects* effects;
	class MyImageEffect* hiteffect;
	struct DodgePlayer
	{
	public:
		DodgePlayer() {
		}
		DodgePlayer(Vec2 p, String filepath) {
			pos = p;
			//NowChip  = A;
			nowChip = A;
			chipCnt = 0;
			flag = 0;
			Cnt = 1;
			Image playerimage = Image(filepath);
			int chipW = playerimage.width() / DODGE_PLAYER_ROW_SIZE;
			int chipH = playerimage.height() / DODGE_PLAYER_LINE_SIZE;
			for (int line = 0; line <DODGE_PLAYER_LINE_SIZE; line++) {
				for (int row = 0; row < DODGE_PLAYER_ROW_SIZE; row++) {
					playerChip[line][row] = new Texture(playerimage.clipped(chipW * row, chipH * line, chipW, chipH));
				}
			}
		}

		bool isBallThrow() {
			if (Cnt>=5)return true;
			else return false;
		}
		void ChangeChip() {	//次のチップを設定
			if (chipCnt == 10) {
				Cnt++;
				chipCnt = 0;
				if (nowChip == A) {
					if (flag == 1)nowChip = D;
					else nowChip = B;
				}
				else if (nowChip == B) {
					nowChip = C; flag = 1;
				}
				else if (nowChip == D)nowChip = E;
				else if (nowChip == E && flag == 1) {
					nowChip = F; flag = 2;
				}
				else if (nowChip == F)nowChip = END;
			}
			chipCnt++;

		}

		//描画
		void draw() {
			//playerChip[Vec2(NowChip ).x][((Vec2) NowChip ).y]->drawAt(pos);
			playerChip[(int)nowChip.x][(int)nowChip.y]->drawAt(pos);
		
		}
		bool drawCompletecheck() {
			if (Cnt>=7)return true;
			else return false;
		}

	private:

		int chipCnt;
		int flag;
		int radius;//Target用当たり判定半径
		Vec2 pos;	//位置
		//USEFULCHIP NowChip ;
		Vec2 nowChip;
		int Cnt;
		Texture* playerChip[DODGE_PLAYER_LINE_SIZE+1][DODGE_PLAYER_ROW_SIZE+1];

	};
	struct Ball {
		Ball() {}
		Ball(Vec2 pos, String filepath, float dVelocity) {
			constexpr float X_WEIGHT = 2;//上昇速度
			constexpr float Y_WEIGHT = -0.5;
			this->pos = pos;
			this->dVelocity = dVelocity;
			//とりま宣言（センサの値とってないから）
			dVelocity = 10;
			texture = Texture(filepath);
			vec = Vec2(dVelocity * X_WEIGHT, dVelocity * Y_WEIGHT);
			angle = 0;
			gravity = 0.3;
			isEnd = false;
		}
		void Move() {
			if (Window::ClientWidth() + texture.width() <= pos.x) {
				isEnd = true;
				return;
			}
			pos += vec;
			vec.y -= gravity;
		}
		void Draw() {
			texture.drawAt(pos);
		}

		//ボールの回転rotate
		Texture texture;
		Vec2 pos;//座標
		Vec2 vec;//移動量
		int angle;
		int gravity;
		float dVelocity;
		bool isEnd;
	};

	
	void judgeHitSensorState();//センサーの値でランク付け
	void judgeHitOrMiss();		//センサーの値とスコープの命中度で総合判定(HIT or MISS)
	void scoreStore();//配列に格納（HIT/MISS velocity hitLevel ）
	SPEED speed;
	MODE nowselect;
	STATE judge =NONE;
	Audio* backAudio;
	Vec2 pSpawn;
	Vec2 bSpawn;
	bool ballDraw;
	struct Ball ball;
	struct DodgePlayer player;
};





