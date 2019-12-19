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
	int countDown;

	//描画
	void scenedraw(void);
};