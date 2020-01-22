#pragma once
#include "MiniGameBase.h"
#include"DodgeSceneBase.h"
#include"DodgeTitle.h"
#include"DodgeGame.h"
#include"DodgeResult.h"
#include"DodgeHitMotion.h"



class Dodge : public MiniGame {
public:
	Dodge(void);
	~Dodge(void);
	bool isReady(void);	//ロード終了してもいいかどうか
	void start(void);	//ロード空けた後に実行されるもの
	void update(void);	//計算処理
	void draw(void);	//描画処理
	void outputResult(void);//結果をDBへ出力する
	void stopGame();	//ゲームを一時中断する
	void restartGame();//ゲーム再開
private:
	DODGE_SCENE nowscene;
	DODGE_SCENE nextscene;
	class DodgeSceneBase* scene;
	void changeScene();
};