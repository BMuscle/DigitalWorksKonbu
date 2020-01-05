#pragma once
#include <Siv3D.hpp>
#include "MyKey.h"
#include "MyRoom.h"
#include "MyImageButton.h"
#include "MyRoomSceneBase.h"
#include "MySceneManager.h"


class MyRoomTitle : public MyRoomSceneBase {

public:
	MyRoomTitle(MYROOM_SCENE* scenep);
	~MyRoomTitle();

	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

private:
	Audio* backAudio;//BGM
	enum MODE {
		EXIT,		//ゲームを終了する
		COLLECTION,	//collection要素を作成する
		NEXTMAP,	//マップへ移動する
		SIZE,
	};

	MyImageButton* button[SIZE];
	String buttonName[SIZE];	//ボタンのアセット名
	MODE selectedMode;			//現状選択されているモード

	//
	//選択されているモードを変更するか処理する
	void moveSelectMode();
	//ボタンの描画
	void drawButton();
};