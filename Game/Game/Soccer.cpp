#include "Soccer.h"

Soccer::Soccer(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"soccerfont", 70);
	FontAsset::Preload(U"soccerfont");
	TextureAsset::Register(U"soccerback", U"resources/images/backs/soccer.png", AssetParameter::LoadAsync());
}
Soccer::~Soccer(void) {
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

}
void Soccer::draw(void) {	//�`�揈��
	TextureAsset(U"soccerback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}
void Soccer::outputResult(void) {//���ʂ�DB�֏o�͂���

}