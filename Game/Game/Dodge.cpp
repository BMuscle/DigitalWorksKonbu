#include "Dodge.h"

Dodge::Dodge(void) {

}
Dodge::~Dodge(void) {

}
bool Dodge::isReady(void) {	//���[�h�I�����Ă��������ǂ���

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

}
void Dodge::outputResult(void) {//���ʂ�DB�֏o�͂���

}