#include "SelectMode.h"


SelectMode::SelectMode(void) {
	//アセットへロード
	FontAsset::Register(U"selectmodefont", 70);
	FontAsset::Preload(U"selectmodefont");
	TextureAsset::Register(U"selectmodeback", U"resources/images/backs/selectmode.png", AssetParameter::LoadAsync());

	TextureAsset::Register(U"selectmodesoccer", U"resources/images/items/selectmode/soccer.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodedodge", U"resources/images/items/selectmode/dodge.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodeshoekick", U"resources/images/items/selectmode/shoekick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodegacha", U"resources/images/items/selectmode/gacha.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodemyroom", U"resources/images/items/selectmode/myroom.png", AssetParameter::LoadAsync());

	//変数の初期化
	selectedMode = MODE::SOCCER;//初期の選択状態をサッカーにする。

}
SelectMode::~SelectMode(void) {
	FontAsset::Unregister(U"selectmodefont");
	TextureAsset::Unregister(U"selectmodeback");

	TextureAsset::Unregister(U"selectmodesoccer");
	TextureAsset::Unregister(U"selectmodedodge");
	TextureAsset::Unregister(U"selectmodeshoekick");
	TextureAsset::Unregister(U"selectmodegacha");
	TextureAsset::Unregister(U"selectmodemyroom");

}
bool SelectMode::isReady(void) {
	if (TextureAsset::IsReady(U"selectmodeback")&&
		TextureAsset::IsReady(U"selectmodesoccer")&&
		TextureAsset::IsReady(U"selectmodedodge")&&
		TextureAsset::IsReady(U"selectmodeshoekick")&&
		TextureAsset::IsReady(U"selectmodegacha")&&
		TextureAsset::IsReady(U"selectmodemyroom")) {
		return true;
	}
	return false;
}
void SelectMode::start(void) {
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/selectmode.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void SelectMode::update(void) {
	if (MyKey::getDecisionKey()) {
		if (getSelectedMode() == MODE::MYROOM) {//マイルームシーンへ移行
			MySceneManager::setNextScene(SCENE::MYROOM);
		}
		else {//ゲームへ移行
			MySceneManager::setNextScene(SCENE::GAME);
		}
	}
}
void SelectMode::draw(void) {
	//背景描画
	TextureAsset(U"selectmodeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}

MODE SelectMode::getSelectedMode() {//選択されているモードを返す。シーン移行時に受け渡す
	return selectedMode;
}