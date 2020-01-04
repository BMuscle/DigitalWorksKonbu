#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "MyRoomTitle.h"
#include "MyRoomCollection.h"
#include "MyRoomSceneBase.h"
#include "SimpleLoadEffect.h"


class MyRoom : public MyScene {
public:
	MyRoom(void);
	~MyRoom(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

private:
	MYROOM_SCENE nowScene;
	MYROOM_SCENE nextScene;

	MyRoomSceneBase* scene;
	SimpleLoadEffect* loadEffect;

	void changeScene();
};
