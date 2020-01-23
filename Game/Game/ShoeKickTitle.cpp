#include "ShoeKickTitle.h"

//��ʒ�������ǂꂾ���{�^��������Ă��邩
#define BUTTON_INTERVAL 300
#define BUTTON_Y Window::ClientHeight() * 0.7

ShoeKickTitle::ShoeKickTitle(SHOEKICK_SCENE* scenep) : ShoeKickSceneBase(scenep){
	TextureAsset::Register(U"shoekick_title", U"resources/images/backs/game/shoekick/title.png", AssetParameter::LoadAsync());

	//�{�^�����[�h
	button[GAME] = new MyImageButton(U"resources/images/items/game/shoekick/title/game", U"", 0, Window::ClientWidth() / 2 + BUTTON_INTERVAL, BUTTON_Y);
	button[MAP] = new MyImageButton(U"resources/images/items/game/shoekick/title/map", U"", 0, Window::ClientWidth() / 2 - BUTTON_INTERVAL, BUTTON_Y);


	selectButton = BUTTON::GAME;//�����{�^���I�����
}
ShoeKickTitle::~ShoeKickTitle() {
	delete backAudio;

	TextureAsset::Unregister(U"shoekick_title");

	delete button[GAME];
	delete button[MAP];
}

bool ShoeKickTitle::isReady(void) {
	if (TextureAsset::IsReady(U"shoekick_title") &&
		button[GAME]->isReady() &&
		button[MAP]->isReady()) {
		return true;
	}
	return false;
}
void ShoeKickTitle::start(void) {
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/shoekick/title.mp3");
	backAudio->setVolume(0.1);
	backAudio->setLoop(true);
	backAudio->play();
}
void ShoeKickTitle::update(void) {

	//�{�^������
	if (MyKey::getDecisionKey()) {//����
		switch (selectButton)
		{
		case ShoeKickTitle::MAP:
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		case ShoeKickTitle::GAME:
			setNextScene(SHOEKICK_SCENE::GAME);
			break;
		}
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}
	else if (MyKey::getRightKeyDown()) {//���ړ�
		selectButton = BUTTON::GAME;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
	else if (MyKey::getLeftKeyDown()) {//���ړ�
		selectButton = BUTTON::MAP;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}

}
void ShoeKickTitle::draw(void) {
	TextureAsset(U"shoekick_title").drawAt(Window::ClientCenter());

	switch (selectButton)
	{
	case ShoeKickTitle::MAP:
		button[MAP]->drawNotWord(true);
		button[GAME]->drawNotWord(false);
		break;
	case ShoeKickTitle::GAME:
		button[MAP]->drawNotWord(false);
		button[GAME]->drawNotWord(true);
		break;
	}
}