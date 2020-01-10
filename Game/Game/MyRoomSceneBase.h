#pragma once
#include "MyRoom.h"

enum class MYROOM_SCENE {
	TITLE,
	REPORT,
	COLLECTION,
	NONE,
};


class MyRoomSceneBase {
private:
	MYROOM_SCENE* nextSceneP;
public:
	MyRoomSceneBase(MYROOM_SCENE* scenep) {
		nextSceneP = scenep;
	}
	virtual ~MyRoomSceneBase(){
	}
	void setNextScene(MYROOM_SCENE scene) {
		*nextSceneP = scene;
	}
	virtual bool isReady() = 0;
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
