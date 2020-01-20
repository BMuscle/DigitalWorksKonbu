#pragma once
#include "MiniGameBase.h"
#include "MySceneManager.h"
#include "SimpleLoadEffect.h"

class Soccer : public MiniGame {
public:
	Soccer(void);
	~Soccer(void);
	bool isReady(void);	//ロード終了してもいいかどうか
	void start(void);	//ロード空けた後に実行されるもの
	void update(void);	//計算処理
	void draw(void);	//描画処理
	void outputResult(void);//結果をDBへ出力する
	void restartGame();//ゲーム再開

private:
	enum SOCCER_SCENE {
		TITLE,
		SELECT_MODE,
		THINKING,
		PRACTICAL_SKILL,
		RESULT,
		INTERRUPTION,

	};
	Audio* backAudio;

	SOCCER_SCENE nowScene, nextScene, oldNowScene;
	int selecttype = 1;//キーパーかキッカーか判断する関数
	int inputBotton = 1;
	int conecttingflag = 0;
	int gachasoccer = 0;//ガチャポイント
	int maxpoint = 0;//最高得点
	int framecount;//フレームカウント
#define maxaccel 50
#define minaccel -50
	void setNextScene(SOCCER_SCENE next);
	void changeScene();
	void startScene();

	void updateTitle();
	void updateSelect();
	void updateThinking();
	void updatePractical_skill();
	void updateResult();
	void drawTitle();
	void drawSelect();
	void drawThinking();
	void drawPractical_skill();
	void drawResult();
	void stopGame();
	bool whichWin(int);
	void frameCount();//フレームカウント
	void soccerGachaPoint();//がちゃぽいんとかさん
	void soccerHighScore(int);//最高得点
	void itemCheck();//ガチャアイテムチェック

	SimpleLoadEffect* loadEffect;

};
