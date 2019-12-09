#pragma once
#include "MyScene.h"
#include "Title.h"
#include "LoadEffect.h"

enum class SCENE {
	TITLE,
	SYNCRC,
	GAME,
	RESULT,
	NONE
};

class MySceneManager {
public:
	MySceneManager() = delete;
	static void initialize();	//初期化
	static void finalize();		//終了化

	static void updateScene();	//シーンの計算処理
	static void drawScene();	//シーンの描画処理
	static void setNextScene(SCENE next);//次フレームにてシーンが移行する
private:
	static LoadEffect* loadEffect;
	static MyScene* scene;		//現在実行中のScene
	static SCENE NOWSCENE;		//現在実行中のSCENE
	static SCENE NEXTSCENE;		//シーン移行時にはNONE以外が入る
	static void changeScene();	//シーン移行
	static bool isLoadFinished;	
};
