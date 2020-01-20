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
	MyKey::setKeyLock(true);
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

void SimpleLoadEffect::nextState() {
	if (loadState == SIMPLE_LOAD_STATE::NONE &&
		loadState == SIMPLE_LOAD_STATE::END) {
		return;
	}
	loadState = (SIMPLE_LOAD_STATE)((int)loadState + 1);
}

//�^���Â̏�ԂɂȂ��Ă��邩�ǂ���TRUE�̏ꍇ���̎��t���[�����疾�邭�Ȃ�n�߂�B
bool SimpleLoadEffect::isDark() {
	if (loadState == SIMPLE_LOAD_STATE::DARK) {
		return true;
	}
	return false;
}

bool SimpleLoadEffect::isDarkWait() {
	if (loadState == SIMPLE_LOAD_STATE::DARK_WAIT) {
		return true;
	}
	return false;
}
//���邭�Ȃ��Ă��邩�ǂ���TRUE�̏ꍇ�I������
bool SimpleLoadEffect::isEnd() {
	if (loadState == SIMPLE_LOAD_STATE::END) {
		loadState = SIMPLE_LOAD_STATE::NONE;
		MyKey::setKeyLock(false);
		return true;
	}
	return false;
}

bool SimpleLoadEffect::isLoad() {
	if (loadState == SIMPLE_LOAD_STATE::NONE) {
		return false;
	}
	return true;
}