#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "MyImageButton.h"

class Gacha : public MyScene {
public:
	Gacha(void);
	~Gacha(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;
	enum class BUTTON {
		GACHA,
		EXIT,
		SIZE,
	};
	MyImageButton* button[(int)BUTTON::SIZE];//画像ボタンクラス
	BUTTON selectedButton;//現在選択されているボタン

	bool nowGachaing;//現在ガチャしているかどうか

	void selectedMove();//現在選択されているものの更新処理

};
