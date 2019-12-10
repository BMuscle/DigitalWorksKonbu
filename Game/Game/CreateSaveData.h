#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "MySqlite3.h"

class CreateSaveData : public MyScene {
public:
	CreateSaveData(void);
	~CreateSaveData(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

private:
	Audio* backAudio;//BGM

	Font nameFont;//名前入力欄用フォント
	TextBox namebox;//名前入力欄
};