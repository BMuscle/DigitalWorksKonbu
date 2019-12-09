#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"

class SelectSaveData : public MyScene {
public:
	SelectSaveData(void);
	~SelectSaveData(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;
};

