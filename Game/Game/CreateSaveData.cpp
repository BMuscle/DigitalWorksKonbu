#include "CreateSaveData.h"

#define NAMEBOX_Y (Window::ClientHeight() * 0.3)
#define ITEM_INTERVAL (Window::ClientHeight() * 0.2)


CreateSaveData::CreateSaveData(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"createSDfont", 70);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());

	//�ϐ��̏�����
	nameFont = Font(60);
	namebox = TextBox(nameFont, Vec2(100, 100), Window::ClientWidth() * 0.6, 15, U"���O����͂��Ă�������");
	namebox.setCenter(Vec2(Window::ClientWidth() / 2, NAMEBOX_Y));
	namebox.setActive(true);//������ԂŃe�L�X�g�{�b�N�X���A�N�e�B�u��
}
CreateSaveData::~CreateSaveData(void) {
	FontAsset::Unregister(U"createSDfont");
	TextureAsset::Unregister(U"createSDback");
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")) {
		return true;
	}
	return false;
}
void CreateSaveData::start(void) {
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void CreateSaveData::update(void) {//�v�Z����
	if (MyKey::getDecisionKey() &&  !namebox.isActive()) {//�e�L�X�g�{�b�N�X�̃G���^�[���͂���

		//���̓`�F�b�N������

		MySceneManager::setNextScene(SCENE::SELECT_MODE);
	}
	if (namebox.isActive()) {
		const auto result = namebox.update();
		if (result == TextBox::State::Enter || result == TextBox::State::Tab) {//Tab��Enter��������Ă���Ȃ玟�ֈړ�����
			//��ŏ㉺�ړ��ŏ����A�o�^�[�I���Ȃǂ��ł���悤�ɁH������Ȃ���Ċ������ʂƂ�
			namebox.setActive(false);//��A�N�e�B�u��
		}

	}
}
void CreateSaveData::draw(void) {//�`�揈��
	//�w�i�`��
	TextureAsset(U"createSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	FontAsset(U"createSDfont")(U"���O").drawAt((Window::ClientWidth() / 2) - (namebox.getRect().w / 2) + FontAsset(U"createSDfont").fontSize(), NAMEBOX_Y - namebox.getRect().h);
	namebox.draw();
	namebox.drawOverlay();
}