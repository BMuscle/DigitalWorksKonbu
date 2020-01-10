#include "MyImageEffect.h"

MyImageEffect::MyImageEffect(String filepath, const int frameX, const int frameY, const float switchingTime) {
	this->switchingTime = switchingTime;//切替時間格納
	this->frameNumber = frameX * frameY;//フレーム数を格納
	Image baseTexture = Image(filepath);
	for (int y = 0; y < baseTexture.height(); y += (baseTexture.height() / frameY)) {
		for (int x = 0; x < baseTexture.width(); x += (baseTexture.width() / frameX)) {
			animationTexture.push_back(Texture(baseTexture.clipped(x, y, (baseTexture.width() / frameX), (baseTexture.height() / frameY))));
		}
	}
	baseTexture.release();//元画像を開放
}
MyImageEffect::~MyImageEffect() {

}
bool MyImageEffect::update(float t, const Vec2& pos) {//オーバライド　計算処理　描画処理も兼ねている
	if (t / switchingTime >= animationTexture.size()) {
		animationTexture.at(animationTexture.size() - 1).drawAt(pos);//順番に描画する
		return false;//描画終了
	}
	animationTexture.at(t / switchingTime).drawAt(pos);//順番に描画する
	return t < (switchingTime * frameNumber);//フレームを全て描画し終えればfalseを返す
}
