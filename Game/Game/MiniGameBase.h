#pragma once
#include "User.h"

class MiniGame {
public:
	MiniGame(void) {}
	virtual ~MiniGame(void) {}
	virtual bool isReady(void) = 0;	//ロード終了してもいいかどうか
	virtual void start(void) = 0;	//ロード空けた後に実行されるもの
	virtual void update(void) = 0;	//計算処理
	virtual void draw(void) = 0;	//描画処理
	virtual void outputResult(void) = 0;//結果をDBへ出力する
	virtual void stopGame() = 0;	//ゲームを一時中断する
};