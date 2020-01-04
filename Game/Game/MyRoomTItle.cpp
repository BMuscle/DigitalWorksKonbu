#include "MyRoomTItle.h"


MyRoomTitle::MyRoomTitle(MYROOM_SCENE* scenep):MyRoomSceneBase(scenep) {
	//アセットのロード
	FontAsset::Register(U"myroomfont", 70);
	FontAsset::Preload(U"myroomfont");
	//背景
	TextureAsset::Register(U"myroomback", U"resources/images/backs/myroom/title.png", AssetParameter::LoadAsync());

	//それぞれボタンON　OFFのロード
	button[MODE::AVATAR] = new MyImageButton(U"resources/images/items/myroom/title/avatar", U"", 10, 100, 100, false);
	button[MODE::COLLECTION] = new MyImageButton(U"resources/images/items/myroom/title/collection", U"", 10, 1000, 100, false);
	button[MODE::NEXTMAP] = new MyImageButton(U"resources/images/items/myroom/title/nextmap", U"", 10, 1000, 900, false);
	button[MODE::EXIT] = new MyImageButton(U"resources/images/items/myroom/title/exit", U"", 10, 100, 900, true);

	//変数の初期化
	selectedMode = NEXTMAP;
}

MyRoomTitle::~MyRoomTitle(void) {
	FontAsset::Unregister(U"myroomfont");
	TextureAsset::Unregister(U"myroomback");
	for (int i = 0; i < MODE::SIZE; i++) {
		delete button[i];
	}
	delete backAudio;
}

bool MyRoomTitle::isReady(void) {
	if (TextureAsset::IsReady(U"myroomback")) {
		for (int i = 0; i < MODE::SIZE; i++) {
			if (!button[i]->isReady()) {
				return false;
			}
		}
		return true;
	}
	return false;
}


void MyRoomTitle::start(void) {
	delete backAudio;
	backAudio = new Audio(U"resources/musics/backs/myroom.wav");
	backAudio->setLoop(true);
	backAudio->play();
}


void MyRoomTitle::update(void) {
	if (MyKey::getDecisionKey()) {
		switch (selectedMode)
		{
		case MyRoomTitle::COLLECTION:
			setNextScene(MYROOM_SCENE::COLLECTION);
			break;
		case MyRoomTitle::AVATAR:
			setNextScene(MYROOM_SCENE::AVATAR);
			break;
		case MyRoomTitle::NEXTMAP:
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		case MyRoomTitle::EXIT:
			System::Exit();
			break;
		default:
			break;
		}
	}

	moveSelectMode();
}

void MyRoomTitle::draw(void) {
	//背景の描画
	TextureAsset(U"myroomback").draw();
	//ボタンの描画
	drawButton();
}



void MyRoomTitle::moveSelectMode() {
	if (MyKey::getLeftKeyDown()) {
		selectedMode = EXIT;
	}
	if (MyKey::getRightKeyDown()) {
		selectedMode = COLLECTION;
	}
	if (MyKey::getDownKeyDown()) {
		selectedMode = NEXTMAP;
	}
}

//それぞれのボタンを全て描画する
void MyRoomTitle::drawButton() {
	for (int i = 0; i < MODE::SIZE; i++) {
		button[i]->drawNotWord(i == selectedMode);
	}
}