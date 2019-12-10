#include "SelectMode.h"


SelectMode::SelectMode(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"selectmodefont", 70);
	FontAsset::Preload(U"selectmodefont");
	TextureAsset::Register(U"selectmodeback", U"resources/images/backs/selectmode.png", AssetParameter::LoadAsync());

	TextureAsset::Register(U"selectmodesoccer", U"resources/images/items/selectmode/soccer.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodedodge", U"resources/images/items/selectmode/dodge.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodeshoekick", U"resources/images/items/selectmode/shoekick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodegacha", U"resources/images/items/selectmode/gacha.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectmodemyroom", U"resources/images/items/selectmode/myroom.png", AssetParameter::LoadAsync());

	//�ϐ��̏�����
	selectedMode = MODE::SOCCER;//�����̑I����Ԃ��T�b�J�[�ɂ���B

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
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/selectmode.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void SelectMode::update(void) {
	if (MyKey::getDecisionKey()) {
		if (getSelectedMode() == MODE::MYROOM) {//�}�C���[���V�[���ֈڍs
			MySceneManager::setNextScene(SCENE::MYROOM);
		}
		else {//�Q�[���ֈڍs
			MySceneManager::setNextScene(SCENE::GAME);
		}
	}
}
void SelectMode::draw(void) {
	//�w�i�`��
	TextureAsset(U"selectmodeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}

MODE SelectMode::getSelectedMode() {//�I������Ă��郂�[�h��Ԃ��B�V�[���ڍs���Ɏ󂯓n��
	return selectedMode;
}