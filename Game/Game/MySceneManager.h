#pragma once
#include "MyScene.h"
#include "LoadEffect.h"
#include "Title.h"
#include "SelectSaveData.h"
#include "CreateSaveData.h"
#include "SelectMode.h"
#include "Game.h"
#include "MyRoom.h"
#include "Gacha.h"

enum class SCENE {//シーンの種類
	TITLE,
	SELECT_SAVEDATA,
	CREATE_SAVEDATA,
	SELECT_MODE,
	GAME,
	MYROOM,
	GACHA,
	NONE
};

class MySceneManager {
public:
	MySceneManager() = delete;
	//初期化
	static void initialize();	
	//終了化
	static void finalize();		
	//シーンの計算処理
	static void updateScene();	
	//シーンの描画処理
	static void drawScene();	
	//シーンの変更要求（次フレームでシーンが移行する)
	static void setNextScene(SCENE next);
private:
	static LoadEffect* loadEffect;//ロードエフェクト
	static bool isLoadFinished;//ロードが完了しているかフラグ
	static MyScene* scene;		//現在実行中のScene
	static SCENE NOWSCENE;		//現在実行中のSCENE
	static SCENE NEXTSCENE;		//シーン移行時にはNONE以外が入る
	static void changeScene();	//シーン移行
	
};
