#pragma once
#include"DodgeSceneBase.h"
#include<Siv3D.hpp>
#include<math.h>
#include "Scope.h"
#include"DodgeCharacter.h"
#include"Sensor.h"

constexpr int DODGE_GAME_PLAY_COUNT = 3;

#define DEFAULT 3

enum STAGE {
	START,
	RULE,
	GAME,
	MOTION,
	STOP,
};

struct Score {
public:
	Score() {
		for (int i = 0; i < DODGE_GAME_PLAY_COUNT; i++) {
			hit[i] = false;
			hitLevel[i] = 0;
			dVelocity[i] = 0;
		}
	}

	bool hit[DODGE_GAME_PLAY_COUNT];
	float hitLevel[DODGE_GAME_PLAY_COUNT];
	float dVelocity[DODGE_GAME_PLAY_COUNT];

private:
};

class DodgeGame :public DodgeSceneBase
{
public:
	DodgeGame(DODGE_SCENE* nextScene, int ballCnt,struct Score score);
	~DodgeGame();
	void start(void);
	void update();
	void draw();
	int getBallCnt();
	float getDVelocity();
	int getHitLevel();
	struct Score getScore();
private:
	//ˆø”
	int ballCnt;
	float dVelocity;
	int hitLevel;
	struct Score score;

	struct BallLife {
	public:
		BallLife() {
		}
		BallLife(Vec2 p,String filepath,int i) {
			pos = p;
			ballimage=Texture(filepath);
			vec = Vec2(i* ballimage.width(),0);
		}

		void Draw() {
			ballimage.draw(pos+vec);
		}
	private:
		Texture ballimage;
		Vec2 pos;	
		Vec2 vec;	//‰E•ûŒüˆÚ“®—Ê
	};

	int flag = 1;
	int radius = 20;
	float movement = 4;
	struct DodgeCharacter target;	
	struct Scope scope;
	Vec2 initial;
	Vec2 spawn;
	Vec2 ballplace;
	Audio* backAudio;
	STAGE nowselect;
	Array<DodgeCharacter> mobs;
	Array<struct BallLife> balllife;
	Texture Scopeimage;
	int HitScopeCheck(int r1, Vec2 z1, int r2, Vec2 z2);
	bool getHitSensorState();
};

