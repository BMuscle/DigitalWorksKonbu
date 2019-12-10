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

class Game : public MyScene {
public:
	Game(MODE gamemode);
	~Game(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;
	MiniGame* minigame;
};