#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"

class Title : public MyScene {
public:
	Title(void);
	~Title(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;
	double alpha;
	void changeAlpha(void);
};

