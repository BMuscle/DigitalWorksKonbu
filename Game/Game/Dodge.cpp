#include "Dodge.h"

Dodge::Dodge(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	TextureAsset::Register(U"dodgeback", U"resources/images/backs/dodge.png", AssetParameter::LoadAsync());
}
Dodge::~Dodge(void) {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;
}
bool Dodge::isReady(void) {	//���[�h�I�����Ă��������ǂ���
	if (TextureAsset::IsReady(U"dodgeback")) {
		return true;
	}
	return false;
}
void Dodge::start(void) {	//���[�h�󂯂���Ɏ��s��������
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void Dodge::update(void) {	//�v�Z����

}
void Dodge::draw(void) {	//�`�揈��
	TextureAsset(U"dodgeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}
void Dodge::outputResult(void) {//���ʂ�DB�֏o�͂���

}