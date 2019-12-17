#include "SelectMode.h"

#define SELECT_INTERVAL_COUNT (60 * 0.3)

SelectMode::SelectMode(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"selectmodefont", 70);
	FontAsset::Preload(U"selectmodefont");
	TextureAsset::Register(U"selectmodeback", U"resources/images/backs/selectmode.png", AssetParameter::LoadAsync());
	//���[�h���ꂼ��W���̉摜
	textureName[(int)MODE::SOCCER] = U"selectmodesoccer";
	textureName[(int)MODE::DODGE] = U"selectmodedodge";
	textureName[(int)MODE::SHOEKICK] = U"selectmodeshoekick";
	textureName[(int)MODE::GACHA] = U"selectmodegacha";
	textureName[(int)MODE::MYROOM] = U"selectmodemyroom";
	TextureAsset::Register(textureName[(int)MODE::SOCCER], U"resources/images/items/selectmode/soccer.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::DODGE], U"resources/images/items/selectmode/dodge.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::SHOEKICK], U"resources/images/items/selectmode/shoekick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::GACHA], U"resources/images/items/selectmode/gacha.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::MYROOM], U"resources/images/items/selectmode/myroom.png", AssetParameter::LoadAsync());
	//���[�h���ꂼ��I������Ă���Ƃ��̉摜
	TextureAsset::Register(textureName[(int)MODE::SOCCER] + U"on", U"resources/images/items/selectmode/socceron.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::DODGE] + U"on", U"resources/images/items/selectmode/dodgeon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::SHOEKICK] + U"on", U"resources/images/items/selectmode/shoekickon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::GACHA] + U"on", U"resources/images/items/selectmode/gachaon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::MYROOM] + U"on", U"resources/images/items/selectmode/myroomon.png", AssetParameter::LoadAsync());

	//���[�h���ꂼ��I������Ă���Ƃ��̐����p�摜
	TextureAsset::Register(textureName[(int)MODE::SOCCER] + U"txt", U"resources/images/items/selectmode/soccertxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::DODGE] + U"txt", U"resources/images/items/selectmode/dodgetxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::SHOEKICK] + U"txt", U"resources/images/items/selectmode/shoekicktxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::GACHA] + U"txt", U"resources/images/items/selectmode/gachatxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::MYROOM] + U"txt", U"resources/images/items/selectmode/myroomtxt.png", AssetParameter::LoadAsync());
	
	//�ϐ��̏�����
	selectedMode = MODE::SOCCER;//�����̑I����Ԃ��T�b�J�[�ɂ���B

}
SelectMode::~SelectMode(void) {
	FontAsset::Unregister(U"selectmodefont");
	TextureAsset::Unregister(U"selectmodeback");
	delete backAudio;
	for (int i = 0; i < (int)MODE::SIZE; i++) {
		TextureAsset::Unregister(textureName[i]);
		TextureAsset::Unregister(textureName[i] + U"on");
		TextureAsset::Unregister(textureName[i] + U"txt");
	}

}
bool SelectMode::isReady(void) {
	if (TextureAsset::IsReady(U"selectmodeback")) {
		for (int i = 0; i < (int)MODE::SIZE; i++) {
			if (!(TextureAsset::IsReady(textureName[i]) &&
				TextureAsset::IsReady(textureName[i] + U"on") &&
				TextureAsset::IsReady(textureName[i] + U"txt"))) {
				return false;
			}
		}
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
	updateFrameCount();//�t���[�����J�E���g�X�V
	if (MyKey::getDecisionKey()) {
		if (getSelectedMode() == MODE::MYROOM) {//�}�C���[���V�[���ֈڍs
			MySceneManager::setNextScene(SCENE::MYROOM);
		}
		else if(getSelectedMode() == MODE::GACHA){//�K�`���ֈڍs
			MySceneManager::setNextScene(SCENE::GACHA);
		}
		else {//�Q�[���ֈڍs
			MySceneManager::setNextScene(SCENE::GAME);
		}
	}
	moveSelectMode();//���[�h�ؑ֏���
}
void SelectMode::draw(void) {
	constexpr Vec2 modeVec[5]{ //���[�h�̉摜�̍��W
				   Vec2(200, 200),//�T�b�J�[
				   Vec2(400,800),//�h�b�W�{�[��
				   Vec2(1920/2,200),//�C��΂�
				   Vec2(1400,800),//�K�`��
				   Vec2(1600,200) };//�����̕���

	//�w�i�`��
	TextureAsset(U"selectmodeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	//�I�𕔕��̕\��
	TextureAsset(textureName[(int)MODE::SOCCER]).drawAt(modeVec[(int)MODE::SOCCER]);
	TextureAsset(textureName[(int)MODE::DODGE]).drawAt(modeVec[(int)MODE::DODGE]);
	TextureAsset(textureName[(int)MODE::SHOEKICK]).drawAt(modeVec[(int)MODE::SHOEKICK]);
	TextureAsset(textureName[(int)MODE::GACHA]).drawAt(modeVec[(int)MODE::GACHA]);
	TextureAsset(textureName[(int)MODE::MYROOM]).drawAt(modeVec[(int)MODE::MYROOM]);
	//���ݑI������Ă���摜�������\������
	TextureAsset(textureName[(int)getSelectedMode()] + U"on").drawAt(modeVec[(int)getSelectedMode()]);
	//���ݑI������Ă�����̂̓��e�摜��\������
	TextureAsset(textureName[(int)getSelectedMode()] + U"txt").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}

MODE SelectMode::getSelectedMode() {//�I������Ă��郂�[�h��Ԃ��B�V�[���ڍs���Ɏ󂯓n��
	return selectedMode;
}


void SelectMode::moveSelectMode() {
	if (MyKey::getUpKeyDown()) {//��L�[����
		switch (selectedMode) {
		case MODE::DODGE:
			selectedMode = MODE::SOCCER;
			break;
		case MODE::GACHA:
			selectedMode = MODE::MYROOM;
			break;
		}
	}
	else if (MyKey::getDownKeyDown()) {//���L�[����
		switch (selectedMode) {
		case MODE::SOCCER:
			selectedMode = MODE::DODGE;
			break;
		case MODE::SHOEKICK:
			selectedMode = MODE::GACHA;
			break;
		case MODE::MYROOM:
			selectedMode = MODE::GACHA;
			break;
		}
	}
	else if (MyKey::getLeftKeyDown()) {//���L�[����
		switch (selectedMode) {
		case MODE::SHOEKICK:
			selectedMode = MODE::SOCCER;
			break;
		case MODE::MYROOM:
			selectedMode = MODE::SHOEKICK;
			break;
		case MODE::GACHA:
			selectedMode = MODE::DODGE;
			break;
		}
	}
	else if (MyKey::getRightKeyDown()) {//�E�L�[����
		switch (selectedMode) {
		case MODE::SOCCER:
			selectedMode = MODE::SHOEKICK;
			break;
		case MODE::DODGE:
			selectedMode = MODE::GACHA;
			break;
		case MODE::SHOEKICK:
			selectedMode = MODE::MYROOM;
			break;
		}
	}
	
}

void SelectMode::updateFrameCount(){
	frameCount++;
	if (frameCount > 60 * 3000) {//����l�`�F�b�N
		frameCount = 0;
	}
}