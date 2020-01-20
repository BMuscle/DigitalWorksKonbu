#pragma once
#include "MiniGameBase.h"
#include <Siv3D.hpp>
#include "ShoeKickGame.h"
#include "ShoeKickTitle.h"
#include "ShoeKickResult.h"
#include "ShoeKickSceneBase.h"
#include "SimpleLoadEffect.h"
#include "Sensor.h"

class ShoeKick : public MiniGame {
public:
	ShoeKick(void);
	~ShoeKick(void);
	bool isReady(void);	//ロード終了してもいいかどうか
	void start(void);	//ロード空けた後に実行されるもの
	void update(void);	//計算処理
	void draw(void);	//描画処理
	void outputResult(void);//結果をDBへ出力する

	void stopGame();	//ゲームを一時中断する
	void restartGame();

private:
	SHOEKICK_SCENE nowScene;
	SHOEKICK_SCENE nextScene;

	ShoeKickSceneBase* scene;
	SimpleLoadEffect* loadEffect;

	bool isStop;

	void changeScene();
};