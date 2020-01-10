#include "MyEffects.h"

MyEffects::MyEffects() {
	stopwatch.start();//�X�g�b�v�E�H�b�`�X�^�[�g
}

MyEffects::~MyEffects() {

}

void MyEffects::add(EffectInterFace* effect, Vec2 pos) {
	EffectPack pack = { effect, pos, stopwatch.sF() };
	effects.push_back(pack);
}

void MyEffects::draw(){
	Print(stopwatch.sF());
	if (0 < effects.size()) {//�G�t�F�N�g�����݂���ꍇ
		auto itr = effects.begin();
		while (itr != effects.end()) {//�S�Ăɑ΂��Čv�Z�`�揈��
			float f = stopwatch.sF();
			if (itr->effect->update(stopwatch.sF() - itr->addTime, itr->pos)) {
				//�`�搳��I��
				itr++;			//���̃C�e���[�^�֍X�V
			}
			else {
				//�`�悪�I�����Ă���ꍇ�폜����
				auto tmp = itr;		//��U�ޔ�������
				itr++;				//���̃C�e���[�^�֍X�V
				effects.erase(tmp);	//���X�g�����������
			}
		}
	}
}

void MyEffects::pause() {
	stopwatch.pause();
}

void MyEffects::resume() {
	stopwatch.resume();
}

bool MyEffects::isPaused() {
	return stopwatch.isPaused();
}

void MyEffects::clear() {
	effects.clear();
}

bool MyEffects::isEmpty() {
	return effects.empty();
}