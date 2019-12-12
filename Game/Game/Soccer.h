#pragma once
#include "MiniGameBase.h"

class Soccer : public MiniGame {
public:
	Soccer(void);
	~Soccer(void);
	bool isReady(void);	//ロード終了してもいいかどうか
	void start(void);	//ロード空けた後に実行されるもの
	void update(void);	//計算処理
	void draw(void);	//描画処理
	void outputResult(void);//結果をDBへ出力する

private:
	enum SOCCER_SCENE {
		TITLE,
		SELECT,
	};
	Audio* backAudio;

	SOCCER_SCENE nowScene, nextScene;
	void setNextScene(SOCCER_SCENE next);
	void changeScene();

	void updateTitle();
	void updateSelect();
	void drawTitle();
	void drawSelect();
};