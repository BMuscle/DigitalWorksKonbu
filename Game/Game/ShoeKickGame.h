#pragma once

#include <Siv3D.hpp>
#include "MySceneManager.h"
#include "ShoeKickSceneBase.h"
#include "GeneralSoundEffects.h"
#include <math.h>
#include "ShoeCharacter.h"
#include "Shoe.h"
#include "ShoeGage.h"

//ガチャアイテム用 キー値は＋1
enum class GACHA_ITEM {
	SPORTS_SHOE,
	ROCKET_BOOSTER,
	WING,
	ROLLER,
	CAT,
	SIZE,
};
#define GROUND Scene::Height() * 0.8

class ShoeKickGame : public ShoeKickSceneBase {
private:

	//取得しているアイテム
	Array<bool> hasItems;

	//共通部分ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

	//変数宣言
	bool isStart;

	Audio* backAudio;

	bool isDescription;//説明表示フラグ

	class ShoeCharacter* character;
	class Shoe* shoe;
	class ShoeGage* shoeGage;

	enum GAME_STATE {
		KICK,
		FLY,
		END,
	};

	GAME_STATE nowGameState;
	GAME_STATE nextGameState;

	int frameCnt;

	float kickPower;	//センサーデータの最大値を取る

	typedef struct _SignBoard {
		Vec2 vec;
		int meter;
	}SignBoard;

	std::vector<SignBoard> boardVec;

	//関数宣言

	void setNextState(GAME_STATE next);
	void changeState();

	void updateKick();
	void drawKick();

	void updateFly();
	void drawFly();

	SignBoard createSignBoard(int meter);

	//KICKの処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

	//変数宣言
	int kickCount;//蹴るまでのカウント

	Texture* countTexture[4];

	//関数宣言

	//蹴る時のカウントダウン
	void updateKickTimer();
	//蹴る時のカウントダウン描画
	void drawKickTimer();

	void setKickTimer(int kicktime);


	//FLYの処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	//座標は中心から動かさず、移動距離に応じて背景を動かす


public:
	ShoeKickGame(SHOEKICK_SCENE* scenep);
	~ShoeKickGame();

	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

	int getMeter();
};
