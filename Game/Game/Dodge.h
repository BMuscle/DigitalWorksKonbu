#pragma once
#include "MiniGameBase.h"

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
private:
	Audio* backAudio;
};