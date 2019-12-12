#include "ShoeKick.h"

ShoeKick::ShoeKick(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"shoekickfont", 70);
	FontAsset::Preload(U"shoekickfont");
	TextureAsset::Register(U"shoekickback", U"resources/images/backs/shoekick.png", AssetParameter::LoadAsync());
}
ShoeKick::~ShoeKick(void) {
	FontAsset::Unregister(U"shoekickfont");
	TextureAsset::Unregister(U"shoekickback");
	delete backAudio;
}
bool ShoeKick::isReady(void) {	//���[�h�I�����Ă��������ǂ���
	if (TextureAsset::IsReady(U"shoekickback")) {
		return true;
	}
	return false;
}
void ShoeKick::start(void) {	//���[�h�󂯂���Ɏ��s��������
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/shoekick.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void ShoeKick::update(void) {	//�v�Z����

}
void ShoeKick::draw(void) {	//�`�揈��
	TextureAsset(U"shoekickback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}
void ShoeKick::outputResult(void) {//���ʂ�DB�֏o�͂���

}