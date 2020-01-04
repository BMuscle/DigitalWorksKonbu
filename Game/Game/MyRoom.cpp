#include "MyRoom.h"

MyRoom::MyRoom(void) {
	scene = new MyRoomTitle(&nextScene);
	loadEffect = new SimpleLoadEffect();
}

MyRoom::~MyRoom(void) {

}

bool MyRoom::isReady(void) {
	if (scene->isReady()) {
		return true;
	}
	return false;
}

void MyRoom::start(void) {

}


void MyRoom::update(void) {
	loadEffect->update();
	if (nowScene != nextScene) {
		if (!loadEffect->isLoad()) {//ロード中ではないなら
			loadEffect->start();//ロードstart
		}
		if (loadEffect->isDark()) {//真っ暗の画面→ロード待機
			loadEffect->nextState();
			changeScene();
		}
		else if (loadEffect->isDarkWait()) {//ロード待機→明るくなり始め
			if (scene->isReady()) {
				loadEffect->nextState();
				nowScene = nextScene;
			}
		}
	}
	if (loadEffect->isEnd()) {//完全に明るくなったのでstart
		scene->start();
	}

	scene->update();
}

void MyRoom::draw(void) {
	scene->draw();
	loadEffect->draw();
}

void MyRoom::changeScene() {
	switch (nextScene)
	{
	case MYROOM_SCENE::TITLE:
		delete scene;
		scene = new MyRoomTitle(&nextScene);
		break;
	case MYROOM_SCENE::AVATAR:
		delete scene;
		scene = new MyRoomCollection(&nextScene);
		break;
	case MYROOM_SCENE::COLLECTION:
		delete scene;
		scene = new MyRoomCollection(&nextScene);
		break;
	default:
		break;
	}
}