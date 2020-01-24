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
void Dodge::restartGame() {
	
}

void Dodge::changeScene() {
	int ballCnt;
	float dVelocity;
	int hitLevel;
	struct Score score;
	switch (nextscene)
	{
	case DODGE_SCENE::TITLE:
		delete scene;
		scene = new DodgeTitle(&nextscene);
		break;
	case DODGE_SCENE::GAME:
		if (nowscene == DODGE_SCENE::MOTION) {
			ballCnt = ((DodgeHitMotion*)scene)->getBallCnt();
			score = ((DodgeHitMotion*)scene)->getScore();
		}
		else{
			ballCnt = DEFAULT;//�ŏ��̃{�[���c�@
		}

		delete scene;
		scene = new DodgeGame(&nextscene, ballCnt,score);
		break;
	case DODGE_SCENE::MOTION:
		ballCnt = ((DodgeGame*)scene)->getBallCnt();
		dVelocity = ((DodgeGame*)scene)->getDVelocity();
		hitLevel = ((DodgeGame*)scene)->getHitLevel();
		score = ((DodgeGame*)scene)->getScore();
		delete scene;
		scene = new DodgeHitMotion(&nextscene, ballCnt, dVelocity, hitLevel,score);
		break;
	case DODGE_SCENE::RESULT:
		delete scene;
		scene = new DodgeResult(&nextscene);
		break;
	default:
		break;
	}
	nowscene = nextscene;
}

