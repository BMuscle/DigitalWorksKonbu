#include "Soccer.h"

Soccer::Soccer(void) {
	//アセットへロード
	FontAsset::Register(U"soccerfont", 70);
	FontAsset::Preload(U"soccerfont");
	TextureAsset::Register(U"soccerback", U"resources/images/backs/soccer.png", AssetParameter::LoadAsync());
}
Soccer::~Soccer(void) {
	//アセットからアンロード
	FontAsset::Unregister(U"soccerfont");
	TextureAsset::Unregister(U"soccerback");
	delete backAudio;
}
bool Soccer::isReady(void) {	//ロード終了してもいいかどうか
	if (TextureAsset::IsReady(U"soccerback")) {
		return true;
	}
	return false;
}
void Soccer::start(void){	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/soccer.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void Soccer::update(void) {	//計算処理
	if (nowScene != nextScene) {//シーンの変更要求が行われていれば切り替える
		changeScene();
	}
	switch (nowScene)//シーンによって計算処理を切り替える
	{
	case Soccer::TITLE:
		updateTitle();
		break;
	case Soccer::SELECT:
		updateSelect();
		break;
	default:
		break;
	}
}
void Soccer::draw(void) {	//描画処理
	TextureAsset(U"soccerback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

	switch (nowScene)//シーンによって描画処理を切り替える
	{
	case Soccer::TITLE:
		drawTitle();
		break;
	case Soccer::SELECT:
		drawSelect();
		break;
	default:
		break;
	}
}
void Soccer::outputResult(void) {//結果をDBへ出力する

}

void Soccer::setNextScene(SOCCER_SCENE next) {//次のシーンへの移行要求を行う
	nextScene = next;
}
void Soccer::changeScene() {//シーンを変更する
	switch (nowScene)
	{
	case Soccer::TITLE:
		//シーンを変更する前に処理したい内容を書く
		//BGM切替等
		break;
	case Soccer::SELECT:

		break;
	default:
		break;
	}
	nowScene = nextScene;//切り替える
}

void Soccer::updateTitle() {

}
void Soccer::updateSelect() {

}
void Soccer::drawTitle() {

}
void Soccer::drawSelect() {

}