#include "Dodge.h"
#include"MyKey.h"

Dodge::Dodge(void) {
	scene =new DodgeTitle(&nextscene);
	nowscene = nextscene = DODGE_SCENE::TITLE;
}
Dodge::~Dodge(void) {

}
bool Dodge::isReady(void) {	//ロード終了してもいいかどうか
	return true;
}
void Dodge::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始

}
void Dodge::update(void) {	//計算処理
	if (nowscene != nextscene) {
		changeScene();
	}
	scene->update();
}
void Dodge::draw(void) {	//描画処理
	scene->draw();
}
void Dodge::outputResult(void) {//結果をDBへ出力する

}
void Dodge::stopGame() {	//ゲームを一時中断する

}
void Dodge::changeScene() {
	switch (nextscene)
	{
	case DODGE_SCENE::TITLE:
		delete scene;
		scene = new DodgeTitle(&nextscene);
		break;
	case DODGE_SCENE::GAME:
		delete scene;
		scene = new DodgeGame(&nextscene);
		break;
	case DODGE_SCENE::RESULT:
		break;
	default:
		break;
	}
	nowscene = nextscene;
}

