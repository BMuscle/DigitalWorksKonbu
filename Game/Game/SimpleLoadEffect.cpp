#include "SimpleLoadEffect.h"

SimpleLoadEffect::SimpleLoadEffect() {
	loadState = SIMPLE_LOAD_STATE::NONE;
}
SimpleLoadEffect::~SimpleLoadEffect() {

}

//ロードを開始させる secondはトータルのロード時間
void SimpleLoadEffect::start(float second) {
	loadSecond = second;
	stopwatch.restart();
	loadState = SIMPLE_LOAD_STATE::DARKING;
	MyKey::setKeyLock(true);
}
//計算処理
void SimpleLoadEffect::update() {
	float endSecond = loadSecond / 2.0;//修了する秒数
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
//描画処理
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

//真っ暗の状態になっているかどうかTRUEの場合その次フレームから明るくなり始める。
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
//明るくなっているかどうかTRUEの場合終了する
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