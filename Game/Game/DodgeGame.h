#pragma once
#include"DodgeSceneBase.h"
#include<Siv3D.hpp>
#include<math.h>
#include "Scope.h"
#include"DodgeCharacter.h"
#include"Sensor.h"

#define DEFAULT 3

enum STAGE {
	START,
	RULE,
	GAME,
	MOTION,
	STOP,
};

class DodgeGame :public DodgeSceneBase
{
public:
	DodgeGame(DODGE_SCENE* nextScene, int ballCnt);
	~DodgeGame();
	void start(void);
	void update();
	void draw();
	int getBallCnt();
	float getDVelocity();
	int getHitLevel();

private:
	int HitScopeCheck(int r1,Vec2 z1,int r2,Vec2 z2);
	bool getHitSensorState();
	//à¯êî
	int ballCnt;
	float dVelocity;
	int hitLevel;



	int flag = 1;
	int radius = 20;
	float movement = 4;
	struct DodgeCharacter target;	
	struct Scope scope;
	Vec2 initial;
	Vec2 spawn;
	Audio* backAudio;
	STAGE nowselect;
	Array<DodgeCharacter> mobs;
	Texture Scopeimage;
	
};