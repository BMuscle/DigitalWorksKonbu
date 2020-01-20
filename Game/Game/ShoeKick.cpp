#include "ShoeKick.h"
#include <Siv3D.hpp>
#include "MyKey.h"
#include <windows.h>
#include "MySocketServer.h"


ShoeKick::ShoeKick(void) {

	scene = new ShoeKickTitle(&nextScene);
	loadEffect = new SimpleLoadEffect();
	isStop = false;
}
ShoeKick::~ShoeKick(void) {
	delete scene;
	delete loadEffect;
}
bool ShoeKick::isReady(void) {	//ロード終了してもいいかどうか
	if (scene->isReady()) {
		return true;
	}
	return false;
}
void ShoeKick::start(void) {	//ロード空けた後に実行されるもの
	scene->start();
}
void ShoeKick::update(void) {	//計算処理
	if (!isStop) {
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

}
void ShoeKick::draw(void) {	//描画処理
	scene->draw();
	loadEffect->draw();

}
void ShoeKick::outputResult(void) {//結果をDBへ出力する
	//Resultで出力してるのでOK
}

void ShoeKick::stopGame() {	//ゲームを一時中断する
	isStop = true;
}

void ShoeKick::restartGame() {
	isStop = false;
}

void ShoeKick::changeScene() {
	int meter;
	switch (nextScene)
	{
	case SHOEKICK_SCENE::TITLE:
		delete scene;
		scene = new ShoeKickTitle(&nextScene);
		break;
	case SHOEKICK_SCENE::GAME:
		delete scene;
		scene = new ShoeKickGame(&nextScene);
		break;
	case SHOEKICK_SCENE::RESULT:
		meter = ((ShoeKickGame*)scene)->getMeter();
		delete scene;
		scene = new ShoeKickResult(&nextScene, meter);
		break;
	}
}