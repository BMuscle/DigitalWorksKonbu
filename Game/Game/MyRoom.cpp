#include "MyRoom.h"

MyRoom::MyRoom(void) {
	//アセットのロード
	FontAsset::Register(U"myroomfont", 70);
	FontAsset::Preload(U"myroomfont");
	//背景
	TextureAsset::Register(U"myroomback", U"resources/images/backs/myroom.png", AssetParameter::LoadAsync());
	//ボタンのアセット名初期化
	buttonName[MODE::AVATAR] = U"myroomavatar";
	buttonName[MODE::COLLECTION] = U"myroomcollection";
	buttonName[MODE::NEXTMAP] = U"myroomnextmap";
	buttonName[MODE::EXIT] = U"myroomexit";

	//それぞれボタンON　OFFのロード
	TextureAsset::Register(buttonName[MODE::AVATAR], U"resources/images/items/myroom/avatar.png", AssetParameter::LoadAsync());
	TextureAsset::Register(buttonName[MODE::AVATAR] + U"on", U"resources/images/items/myroom/avataron.png", AssetParameter::LoadAsync());
	TextureAsset::Register(buttonName[MODE::COLLECTION], U"resources/images/items/myroom/collection.png", AssetParameter::LoadAsync());
	TextureAsset::Register(buttonName[MODE::COLLECTION] + U"on", U"resources/images/items/myroom/collectionon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(buttonName[MODE::NEXTMAP], U"resources/images/items/myroom/nextmap.png", AssetParameter::LoadAsync());
	TextureAsset::Register(buttonName[MODE::NEXTMAP] + U"on", U"resources/images/items/myroom/nextmapon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(buttonName[MODE::EXIT], U"resources/images/items/myroom/exit.png", AssetParameter::LoadAsync());
	TextureAsset::Register(buttonName[MODE::EXIT] + U"on", U"resources/images/items/myroom/exiton.png", AssetParameter::LoadAsync());

	//変数の初期化
	MODE selectedMode = EXIT;
}

MyRoom::~MyRoom(void) {
	FontAsset::Unregister(U"myroomfont");
	TextureAsset::Unregister(U"myroomback");
	for (int i = 0; i < MODE::SIZE; i++) {
		TextureAsset::Unregister(buttonName[i]);
		TextureAsset::Unregister(buttonName[i] + U"on");
	}
	delete backAudio;
}

bool MyRoom::isReady(void) {
	if (TextureAsset::IsReady(U"myroomback")) {
		for (int i = 0; i < MODE::SIZE; i++) {
			if (!(TextureAsset::IsReady(buttonName[i]) &&
				TextureAsset::IsReady(buttonName[i] + U"on"))) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void MyRoom::start(void) {
	delete backAudio;
	backAudio = new Audio(U"resources/musics/backs/myroom.wav");
	backAudio->setLoop(true);
	backAudio->play();
}


void MyRoom::update(void) {

}

void MyRoom::draw(void) {
	//背景の描画
	TextureAsset(U"myroomback").draw();
	//ボタンの描画
	drawButton();
}

void MyRoom::moveSelectMode() {
	
}

//それぞれのボタンを全て描画する
void MyRoom::drawButton() {
	TextureAsset(buttonName[MODE::AVATAR]).drawAt(200, 100);
	TextureAsset(buttonName[MODE::COLLECTION]).drawAt(1600, 300);
	TextureAsset(buttonName[MODE::NEXTMAP]).drawAt(1000, 800);
	TextureAsset(buttonName[MODE::EXIT]).drawAt(200, 800);
}