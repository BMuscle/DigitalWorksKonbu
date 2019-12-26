#pragma once
#include "MyRoom.h"
#include "MyKey.h"
#include "User.h"
#include <Siv3D.hpp>
#include "MyRoomSceneBase.h"

class MyRoomAvatar : public MyRoomSceneBase{
private:


public:
	MyRoomAvatar(MYROOM_SCENE* scenep);
	~MyRoomAvatar();
	bool isReady();
	void start();
	void update();
	void draw();
};