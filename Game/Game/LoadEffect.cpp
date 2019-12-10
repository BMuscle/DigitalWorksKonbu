#include "LoadEffect.h"

constexpr float alphaSpeed = 1.0 / 60.0 * 2.0;//暗転するスピード

LoadEffect::LoadEffect() {
	loadState = LOAD_STATE::NONE;
	alpha = 0;
}
LoadEffect::~LoadEffect() {

}
void LoadEffect::loadStart() {//ロードを開始する
	loadState = LOAD_STATE::DARKING;
}
void LoadEffect::nextState() {//ロード状態を次の状態へ進める
	loadState = (LOAD_STATE)((int)loadState + 1);
	if (loadState == LOAD_STATE::END) {//範囲チェック
		loadState = LOAD_STATE::NONE;
	}
}
void LoadEffect::update() {
	switch (loadState)
	{
	case LOAD_STATE::DARKING:
		alpha += alphaSpeed;
		if (alpha >= 1) {
			nextState();
		}
		break;
	case LOAD_STATE::BRIGHTING:
		alpha -= alphaSpeed;
		if (alpha <= 0) {
			nextState();
		}
		break;
	case LOAD_STATE::END:
		alpha = 0;
		break;
	default:
		break;
	}
}
void LoadEffect::draw() {
	if (loadState != LOAD_STATE::NONE) {
		Rect(0, 0, Window::ClientWidth(), Window::ClientHeight()).draw(ColorF(0, 0, 0, alpha));
	}
}

LOAD_STATE LoadEffect::getLoadState() {
	return loadState;
}