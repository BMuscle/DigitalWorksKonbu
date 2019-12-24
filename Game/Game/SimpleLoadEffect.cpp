#include "SimpleLoadEffect.h"

SimpleLoadEffect::SimpleLoadEffect() {
	loadState = SIMPLE_LOAD_STATE::NONE;
}
SimpleLoadEffect::~SimpleLoadEffect() {

}

//���[�h���J�n������ second�̓g�[�^���̃��[�h����
void SimpleLoadEffect::start(float second) {
	loadSecond = second;
	stopwatch.restart();
	loadState = SIMPLE_LOAD_STATE::DARKING;
	//�����Ȃ�L�[���b�N
}
//�v�Z����
void SimpleLoadEffect::update() {
	float endSecond = loadSecond / 2.0;//�C������b��
	switch (loadState)
	{
	case SimpleLoadEffect::SIMPLE_LOAD_STATE::NONE:
		break;
	case SimpleLoadEffect::SIMPLE_LOAD_STATE::DARKING:

		if (endSecond <= stopwatch.sF()) {
			loadState = SIMPLE_LOAD_STATE::DARK;
			alpha = 1;
		}
		else {
			alpha = stopwatch.sF() / endSecond;
		}
		break;
	case SimpleLoadEffect::SIMPLE_LOAD_STATE::DARK:
		break;
	case SimpleLoadEffect::SIMPLE_LOAD_STATE::BRIGHTING:
		if (loadSecond <= stopwatch.sF()) {
			loadState = SIMPLE_LOAD_STATE::END;
			alpha = 0;
		}
		else {
			alpha = 1.0 - (stopwatch.sF() - endSecond) / endSecond;
		}
		break;
	case SimpleLoadEffect::SIMPLE_LOAD_STATE::END:
		break;
	default:
		break;
	}
}
//�`�揈��
void SimpleLoadEffect::draw() {
	if (loadState != SIMPLE_LOAD_STATE::NONE) {
		Rect(0, 0, Window::ClientWidth(), Window::ClientHeight()).draw(ColorF(0, 0, 0, alpha));
	}
}

//�^���Â̏�ԂɂȂ��Ă��邩�ǂ���TRUE�̏ꍇ���̎��t���[�����疾�邭�Ȃ�n�߂�B
bool SimpleLoadEffect::isDark() {
	if (loadState == SIMPLE_LOAD_STATE::DARK) {
		loadState = SIMPLE_LOAD_STATE::BRIGHTING;
		return true;
	}
	return false;
}
//���邭�Ȃ��Ă��邩�ǂ���TRUE�̏ꍇ�I������
bool SimpleLoadEffect::isEnd() {
	if (loadState == SIMPLE_LOAD_STATE::END) {
		loadState = SIMPLE_LOAD_STATE::NONE;
		//�����Ȃ�L�[���b�N����
		return true;
	}
	return false;
}

bool SimpleLoadEffect::isLoad() {
	if (loadState == SIMPLE_LOAD_STATE::NONE || loadState == SIMPLE_LOAD_STATE::END) {
		return false;
	}
	return true;
}