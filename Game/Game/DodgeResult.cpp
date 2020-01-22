#include"DodgeResult.h"


DodgeResult::DodgeResult(DODGE_SCENE* nextScene) :DodgeSceneBase(nextScene) {
	TextureAsset::Register(U"dodgeresult", U"resources/images/backs/result.png");

}
DodgeResult::~DodgeResult() {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;
}

void DodgeResult::start(void) {	//���[�h�󂯂���Ɏ��s��������
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}

void DodgeResult::update() {
	if (MyKey::getRightKeyDown()) {//�E�L�[����
		nowselect = MAP;
	}
	else if (MyKey::getLeftKeyDown()) {//���L�[����
		nowselect =TITLE;
	}
	else if (MyKey::getDecisionKey()) {
		switch (nowselect)
		{
		case DodgeResult::MAP:
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		case DodgeResult::TITLE:
			setNextScene(DODGE_SCENE::TITLE);
			break;
		default:
			break;
		}
	}
}

void DodgeResult::draw() {

	TextureAsset(U"dodgeresult").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

}
