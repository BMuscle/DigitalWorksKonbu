#pragma once
#include "MiniGameBase.h"
#include <Siv3D.hpp>

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

private:
	Audio* backAudio;



	//シーン変更用
	enum SCENE {
		TITLE,
		KICK,
		FLY,
		FALL,
		RESULT,
	};
	SCENE nowScene, nextScene;
	void changeScene();
	void setNextScene(SCENE next);

	//蹴るシーンの変数
	bool countDownFunc();
	int countDown;
	bool isNext;

	//描画
	void scenedraw();

	//距離の変数
	int distance, x;
};