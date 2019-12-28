#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "MySqlite3.h"
#include "MyImageButton.h"
#include "TotalPlayTimeTimer.h"

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
	bool isStart;//ロードが終わっているかどうかのフラグ

	Font nameFont;//名前入力欄用フォント
	TextBox namebox;//名前入力欄
	enum class BUTTON {
		RETURN,
		DECISION,
		SIZE,
	};

	enum class SELECT_STATE {
		RETURN,
		TEXT,
		DECISION,
		POPUP,
	};
	SELECT_STATE selectState;
	MyImageButton* button[(int)BUTTON::SIZE];//左右の戻るボタン決定ボタン

	enum class POPUP {//ポップアップの状態
		RETURN,
		DECISION,
		SIZE,
		NONE,
	};
	POPUP popUpState;//ポップアップの選択状態
	MyImageButton* popUpButton[(int)POPUP::SIZE];//左右の戻るボタン決定ボタン
	void selectUpdate();//現在の移動状態に対応する計算処理
	void selectMove();//選択状態の移動チェック＆移動処理
	void popUpDraw();//ポップアップの描画
	
};