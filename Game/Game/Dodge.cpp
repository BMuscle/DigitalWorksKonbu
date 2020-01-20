#include "Dodge.h"
#include"MyKey.h"

Dodge::Dodge(void) {
	scene =new DodgeTitle(&nextscene);
	nowscene = nextscene = DODGE_SCENE::TITLE;
}
Dodge::~Dodge(void) {

}
bool Dodge::isReady(void) {	//���[�h�I�����Ă��������ǂ���
	return true;
}
void Dodge::start(void) {	//���[�h�󂯂���Ɏ��s��������
	//BGM�Đ��J�n

}
void Dodge::update(void) {	//�v�Z����
	if (nowscene != nextscene) {
		changeScene();
	}
	scene->update();
}
void Dodge::draw(void) {	//�`�揈��
	scene->draw();
}
void Dodge::outputResult(void) {//���ʂ�DB�֏o�͂���

}
void Dodge::stopGame() {	//�Q�[�����ꎞ���f����

}
void Dodge::changeScene() {
	switch (nextscene)
	{
	case DODGE_SCENE::TITLE:
		delete scene;
		scene = new DodgeTitle(&nextscene);
		break;
	case DODGE_SCENE::GAME:
		delete scene;
		scene = new DodgeGame(&nextscene);
		break;
	case DODGE_SCENE::RESULT:
		break;
	default:
		break;
	}
	nowscene = nextscene;
}

