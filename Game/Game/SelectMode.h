#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "Mode.h"

class SelectMode : public MyScene {
public:
	SelectMode(void);
	~SelectMode(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

	MODE getSelectedMode();//選択されているモードを返す。シーン移行時に受け渡す
private:
	Audio* backAudio;
	MODE selectedMode;//現在選択されているモード
};
