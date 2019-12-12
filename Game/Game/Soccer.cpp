#include "Soccer.h"

Soccer::Soccer(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"soccerfont", 70);
	FontAsset::Preload(U"soccerfont");
	TextureAsset::Register(U"soccerback", U"resources/images/backs/soccer.png", AssetParameter::LoadAsync());
}
Soccer::~Soccer(void) {
	//�A�Z�b�g����A�����[�h
	FontAsset::Unregister(U"soccerfont");
	TextureAsset::Unregister(U"soccerback");
	delete backAudio;
}
bool Soccer::isReady(void) {	//���[�h�I�����Ă��������ǂ���
	if (TextureAsset::IsReady(U"soccerback")) {
		return true;
	}
	return false;
}
void Soccer::start(void){	//���[�h�󂯂���Ɏ��s��������
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/soccer.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void Soccer::update(void) {	//�v�Z����
	if (nowScene != nextScene) {//�V�[���̕ύX�v�����s���Ă���ΐ؂�ւ���
		changeScene();
	}
	switch (nowScene)//�V�[���ɂ���Čv�Z������؂�ւ���
	{
	case Soccer::TITLE:
		updateTitle();
		break;
	case Soccer::SELECT:
		updateSelect();
		break;
	default:
		break;
	}
}
void Soccer::draw(void) {	//�`�揈��
	TextureAsset(U"soccerback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

	switch (nowScene)//�V�[���ɂ���ĕ`�揈����؂�ւ���
	{
	case Soccer::TITLE:
		drawTitle();
		break;
	case Soccer::SELECT:
		drawSelect();
		break;
	default:
		break;
	}
}
void Soccer::outputResult(void) {//���ʂ�DB�֏o�͂���

}

void Soccer::setNextScene(SOCCER_SCENE next) {//���̃V�[���ւ̈ڍs�v�����s��
	nextScene = next;
}
void Soccer::changeScene() {//�V�[����ύX����
	switch (nowScene)
	{
	case Soccer::TITLE:
		//�V�[����ύX����O�ɏ������������e������
		//BGM�ؑ֓�
		break;
	case Soccer::SELECT:

		break;
	default:
		break;
	}
	nowScene = nextScene;//�؂�ւ���
}

void Soccer::updateTitle() {

}
void Soccer::updateSelect() {

}
void Soccer::drawTitle() {

}
void Soccer::drawSelect() {

}