#include "MyImageButton.h"

MyImageButton::MyImageButton(String path, String word, int fontsize, int x, int y, bool initselect) {
	folderpath = path;
	TextureAsset::Register(path + U"/on.png", path + U"/on.png", AssetParameter::LoadAsync());
	TextureAsset::Register(path + U"/off.png", path + U"/off.png", AssetParameter::LoadAsync());
	font = Font(fontsize);
	drawWord = word;
	buttonX = x;
	buttonY = y;
	selected = initselect;
	buttonAlpha = 1.0;
}
MyImageButton::~MyImageButton() {
	TextureAsset::Unregister(folderpath + U"/off.png");
	TextureAsset::Unregister(folderpath + U"/on.png");
	font.release();
}
bool MyImageButton::isReady() {
	if (TextureAsset::IsReady(folderpath + U"/off.png") &&
		TextureAsset::IsReady(folderpath + U"/on.png")) {
		return true;
	}
	return false;
}
void MyImageButton::setAlpha(float alpha) {
	buttonAlpha = alpha;
}
void MyImageButton::draw(ColorF color) {
	if (selected) {
		TextureAsset(folderpath + U"/on.png").drawAt(buttonX, buttonY, AlphaF(buttonAlpha));
	}
	else {
		TextureAsset(folderpath + U"/off.png").drawAt(buttonX, buttonY, AlphaF(buttonAlpha));
	}
	font(drawWord).drawAt(buttonX, buttonY, color);
}
void MyImageButton::setSelect(bool flag) {//セレクトされているか状態をセットする
	selected = flag;
}
bool MyImageButton::isSelect() {//セレクト状態を返す
	return selected;
}