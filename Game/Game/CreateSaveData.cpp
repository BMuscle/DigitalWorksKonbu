#include "CreateSaveData.h"

#define NAMEBOX_X (Window::ClientWidth() * 0.6)
#define NAMEBOX_Y (Window::ClientHeight() * 0.8)
#define NAMEBOX_W (Window::ClientWidth() * 0.3)
#define ITEM_INTERVAL (Window::ClientHeight() * 0.2)

#define POPUP_INTERVAL (Window::ClientWidth() * 0.07)

CreateSaveData::CreateSaveData(void) {
	isStart = false;
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"createSDfont", 70);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());
	//�|�b�v�A�b�v���[�h
	TextureAsset::Register(U"createSDpopup", U"resources/images/items/createsavedata/popup.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDyes", U"resources/images/items/createsavedata/yes.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDyeson", U"resources/images/items/createsavedata/yeson.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDno", U"resources/images/items/createsavedata/no.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDnoon", U"resources/images/items/createsavedata/noon.png", AssetParameter::LoadAsync());

	//�ϐ��̏�����
	nameFont = Font(50);//�e�L�X�g�{�b�N�X�̃t�H���g
	namebox = TextBox(nameFont, Vec2(100, 100), NAMEBOX_W, 15, U"");
	namebox.setCenter(Vec2(NAMEBOX_X, NAMEBOX_Y));
	namebox.setActive(false);//������ԂŃe�L�X�g�{�b�N�X���A�N�e�B�u��
	popUpState = POPUP_STATE::YES;//�|�b�v�A�b�v�I���̏�����Ԃ�YES��
}
CreateSaveData::~CreateSaveData(void) {
	FontAsset::Unregister(U"createSDfont");
	TextureAsset::Unregister(U"createSDback");
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")&&
		TextureAsset::IsReady(U"createSDpopup")&&
		TextureAsset::IsReady(U"createSDyes")&&
		TextureAsset::IsReady(U"createSDyeson")&&
		TextureAsset::IsReady(U"createSDno")&&
		TextureAsset::IsReady(U"createSDnoon")) {
		return true;
	}
	return false;
}
void CreateSaveData::start(void) {
	isStart = true;
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->play();
	namebox.setActive(true);//���[�h�I����Ńe�L�X�g�{�b�N�X���A�N�e�B�u��
}
void CreateSaveData::update(void) {//�v�Z����

	if (namebox.isActive()) {//�e�L�X�g�{�b�N�X���A�N�e�B�u�̎�
		namebox.update();
		//���̓`�F�b�N������
		if (namebox.getText().isEmpty()) {//�����񂪋�Ȃ�I������
			namebox.setActive(true);
			return;
		}
	}
	else if (MyKey::getDecisionKey()) {//�e�L�X�g�{�b�N�X����A�N�e�B�u�Ō���L�[�������ꂽ��
		switch (popUpState)
		{
		case CreateSaveData::POPUP_STATE::YES://���[�h�I���ֈړ�
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		case CreateSaveData::POPUP_STATE::NO://�Z�[�u�f�[�^�I���֖߂�
			MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);
			break;
		}
	}
	else {//�e�L�X�g�{�b�N�X����A�N�e�B�u�̎��I���̉��ړ�
		if (MyKey::getLeftKeyDown()) {
			popUpState = POPUP_STATE::YES;
		}
		if (MyKey::getRightKeyDown()) {
			popUpState = POPUP_STATE::NO;
		}
	}
}
void CreateSaveData::draw(void) {//�`�揈��
	//�w�i�`��
	TextureAsset(U"createSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	namebox.draw();
	namebox.drawOverlay();
	FontAsset(U"createSDfont")(U"�{�l����").drawAt(NAMEBOX_X - FontAsset(U"createSDfont").fontSize() * 3 - NAMEBOX_W / 2, NAMEBOX_Y, ColorF(0, 0, 0));
	if (!namebox.isActive() && isStart) {//�e�L�X�g�{�b�N�X����A�N�e�B�u�̎��|�b�v�A�b�v��\������
		popUpDraw();
	}
}

void CreateSaveData::popUpDraw() {//�|�b�v�A�b�v�̕`��
	TextureAsset(U"createSDpopup").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	switch (popUpState)
	{
	case CreateSaveData::POPUP_STATE::YES://YES���I������Ă���Ƃ�
		TextureAsset(U"createSDno").drawAt(Window::ClientWidth() / 2 + POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		TextureAsset(U"createSDyeson").drawAt(Window::ClientWidth() / 2 - POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		break;
	case CreateSaveData::POPUP_STATE::NO://NO���I������Ă���Ƃ�
		TextureAsset(U"createSDnoon").drawAt(Window::ClientWidth() / 2 + POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		TextureAsset(U"createSDyes").drawAt(Window::ClientWidth() / 2 - POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		break;
	}
}