#include"DodgeTitle.h"


DodgeTitle::DodgeTitle(DODGE_SCENE* nextScene):DodgeSceneBase(nextScene){
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	TextureAsset::Register(U"dodgeback", U"resources/images/backs/dodge.png", AssetParameter::LoadAsync());

}
DodgeTitle::~DodgeTitle() {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;
}
void DodgeTitle::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void DodgeTitle::update() {
	if (MyKey::getUpKeyDown()) {//上キー入力
		nowselect = GAME;
	}
	else if (MyKey::getDownKeyDown()) {//下キー入力
		nowselect = MAP;
	}
	else if (MyKey::getDecisionKey()) {
		switch (nowselect)
		{
		case DodgeTitle::MAP:
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		case DodgeTitle::GAME:
			setNextScene(DODGE_SCENE::GAME);
			break;
		default:
			break;
		}
	}
}
void DodgeTitle::draw() {
	
	TextureAsset(U"dodgeback").drawAt(Scene::Width() / 2, Scene::Height() / 2);

}
