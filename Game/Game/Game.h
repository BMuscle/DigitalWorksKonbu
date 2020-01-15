#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "Mode.h"
#include "MiniGameBase.h"
#include "Soccer.h"
#include "ShoeKick.h"
#include "Dodge.h"
#include "MySocketServer.h"
#include "MyImageButton.h"
#include "GeneralSoundEffects.h"

class Game : public MyScene {
public:
	Game(MODE gamemode);
	~Game(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	MiniGame* minigame;
	bool isStop;//ゲームが停止状態かどうか
	enum class POPUP {//ポップアップの状態
		RESTART,
		NEXTMAP,
		SIZE,
		NONE,
	};
	POPUP popUpState;//ポップアップの選択状態
	MyImageButton* popUpButton[(int)POPUP::SIZE];//左右の戻るボタン決定ボタン
};