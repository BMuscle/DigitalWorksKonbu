#include "ShoeKick.h"

ShoeKick::ShoeKick(void) {

}
ShoeKick::~ShoeKick(void) {

}
bool ShoeKick::isReady(void) {	//���[�h�I�����Ă��������ǂ���

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

}
void ShoeKick::outputResult(void) {//���ʂ�DB�֏o�͂���

}