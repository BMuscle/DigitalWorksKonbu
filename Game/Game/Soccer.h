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
		BEFORE_THINKING,
		THINKING,
		PRACTICAL_SKILL,
		RESULT,
		INTERRUPTION,

	};
	Audio* backAudio;

	SOCCER_SCENE nowScene, nextScene, oldNowScene;
	int selecttype = 0;//キーパーかキッカーか判断する関数
	int inputRBotton = 1;
	int inputUBotton = 1;
	int conecttingflag = 0;
	int gachasoccer = 0;//ガチャポイント
	int maxpoint = 0;//最高得点
	int framecount;//フレームカウント
	int coutdown = 240;		//カウントダウンは3秒だが、①秒間SHOOTを表示するため、計4秒のカウントダウンを入れる
	int countdownflag = 0;
	int thinkdrawflag = 0;
	int shootpower = 0;
	int direction_flag = 0;
	int shootdirection = 0;
	int stopflag = 0;
	int winflag = 0;
	int flykeeper;
	int reactionspeed;
	int soccerboalcount = 120;
	int end_flag = 0;
	int endcount = 0;
	int highshootpower;
	int hightdirection;
	int xplus = 0;
	int xminus = 0;
	int readflag = 0;
#define maxaccel 40
#define minaccel 10
#define gachapo 250//一回ゲームやるときに加算されるポイント
#define highScorepoint 1000 //最高得点の一番上

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
	void whichWin(int, int);
	void frameCount();//フレームカウント
	void soccerGachaPoint();//がちゃぽいんとかさん
	void soccerHighScore(int);//最高得点
	void itemCheck();//ガチャアイテムチェック

	void updateBeforeThiking();
	void drawBeforeThiking();

	SimpleLoadEffect* loadEffect;

	bool isStop;

	int acex;

	bool endMusic;

};
