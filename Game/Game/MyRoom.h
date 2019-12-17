#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"

class MyRoom : public MyScene {
public:
	MyRoom(void);
	~MyRoom(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;//BGM
	enum MODE {
		COLLECTION,	//collection要素を作成する
		AVATAR,		//アバターを変更する
		NEXTMAP,	//マップへ移動する
		EXIT,		//ゲームを終了する
		SIZE,
	};
	
	String buttonName[SIZE];//ボタンのアセット名
	MODE selectedMode;//現状選択されているモード

	//選択されているモードを変更するか処理する
	void moveSelectMode();
	//ボタンの描画
	void drawButton();
};