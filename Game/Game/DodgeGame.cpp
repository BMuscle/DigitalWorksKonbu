/*
#include"DodgeGame.h"

DodgeGame::DodgeGame(DODGE_SCENE* nextScene) :DodgeSceneBase(nextScene) {
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	TextureAsset::Register(U"dodgeback", U"resources/images/backs/dodge.png", AssetParameter::LoadAsync());

}
DodgeGame::~DodgeGame() {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;
}
void DodgeGame::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void DodgeGame::update() {

}
void DodgeGame::draw() {
	TextureAsset(U"dodgeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

}
*/
