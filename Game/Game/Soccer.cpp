#include "Soccer.h"

Soccer::Soccer(void) {

}
Soccer::~Soccer(void) {

}
bool Soccer::isReady(void) {	//���[�h�I�����Ă��������ǂ���

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

}
void Soccer::outputResult(void) {//���ʂ�DB�֏o�͂���

}