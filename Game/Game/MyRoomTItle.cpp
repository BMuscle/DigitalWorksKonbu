#include "MyRoomTItle.h"


MyRoomTitle::MyRoomTitle(MYROOM_SCENE* scenep):MyRoomSceneBase(scenep) {
	//アセットのロード
	FontAsset::Register(U"myroomfont", 70);
	FontAsset::Preload(U"myroomfont");
	//背景
	TextureAsset::Register(U"myroomback", U"resources/images/backs/myroom/title.png", AssetParameter::LoadAsync());
	//それぞれボタンON　OFFのロード
	button[MODE::REPORT] = new MyImageButton(U"resources/images/items/myroom/title/button/report", U"", 10, Window::ClientWidth() * 0.443, 650, false);
	button[MODE::COLLECTION] = new MyImageButton(U"resources/images/items/myroom/title/button/collection", U"", 10, Window::ClientWidth() * 0.684, 650, false);
	button[MODE::NEXTMAP] = new MyImageButton(U"resources/images/items/myroom/title/button/nextmap", U"", 10, Window::ClientWidth() - 195, 500, false);
	button[MODE::EXIT] = new MyImageButton(U"resources/images/items/myroom/title/button/exit", U"", 10, 300, 800, true);

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
	backAudio = new Audio(U"resources/musics/backs/myroomtitle.wav");
	backAudio->setVolume(0.1);
	backAudio->setLoop(true);
	backAudio->play();
}


void MyRoomTitle::update(void) {
	if (MyKey::getDecisionKey()) {
		switch (selectedMode)
		{
		case MyRoomTitle::REPORT:
			setNextScene(MYROOM_SCENE::REPORT);
			break;
		case MyRoomTitle::COLLECTION:
			setNextScene(MYROOM_SCENE::COLLECTION);
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
		GeneralSoundEffects::play(SE_NAME::DECISION);
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
	int tmp = selectedMode;
	if (MyKey::getLeftKeyDown()) {
		tmp--;
		if (tmp < 0) {
			tmp = 0;
		}
	}
	if (MyKey::getRightKeyDown()) {
		tmp++;
		if (tmp >= MODE::SIZE) {
			tmp = MODE::NEXTMAP;
		}
	}
	if (selectedMode != tmp) {
		selectedMode = (MODE)tmp;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
}

//それぞれのボタンを全て描画する
void MyRoomTitle::drawButton() {
	for (int i = 0; i < MODE::SIZE; i++) {
		button[i]->drawNotWord(i == selectedMode);
	}
}