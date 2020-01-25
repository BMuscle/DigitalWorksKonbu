#include"DodgeTitle.h"


DodgeTitle::DodgeTitle(DODGE_SCENE* nextScene):DodgeSceneBase(nextScene){
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	TextureAsset::Register(U"dodgeback", U"resources/images/items/game/dodge/back.png");
	TextureAsset::Register(U"mapon", U"resources/images/items/game/dodge/button/scenetitle/mapon.png");
	TextureAsset::Register(U"mapoff", U"resources/images/items/game/dodge/button/scenetitle/mapoff.png");
	TextureAsset::Register(U"gameon", U"resources/images/items/game/dodge/button/scenetitle/gameon.png");
	TextureAsset::Register(U"gameoff", U"resources/images/items/game/dodge/button/scenetitle/gameoff.png");
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
	if (MyKey::getRightKeyDown()) {//右キー入力
		nowselect = GAME;
	}
	else if (MyKey::getLeftKeyDown()) {//左キー入力
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
	TextureAsset(U"dodgeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	switch (nowselect)
	{
	case MAP:
		TextureAsset(U"mapon").drawAt(250,500);
		TextureAsset(U"gameoff").drawAt(1670,500);
		break;
	case GAME:
		TextureAsset(U"gameon").drawAt(1670, 500);
		TextureAsset(U"mapoff").drawAt(250, 500);
		break;
	default:
		break;
	}
	

}
