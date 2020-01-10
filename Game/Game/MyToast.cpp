#include "MyToast.h"

MyToast::MyToast(String message, const int fontSize, ColorF colorF, const float endSecondF, const float flushSecondF) {
	this->message = message;
	this->fontSize = fontSize;
	this->colorF = colorF;
	this->endSecondF = endSecondF;
	this->flushSecondF = flushSecondF;
	if (!FontAsset::IsRegistered(U"toast" + Format(fontSize))) {//フォントが登録されていない
		FontAsset::Register(U"toast" + Format(fontSize), fontSize);
		FontAsset::Preload(U"toast" + Format(fontSize));
	}
	
}
MyToast::~MyToast() {

}
bool MyToast::update(float t, const Vec2& pos) {//オーバライド　計算処理　描画処理も兼ねている
	if (t <= flushSecondF) {//表示し始め
		FontAsset(U"toast" + Format(fontSize))(message).drawAt(pos, ColorF(colorF, t / flushSecondF));
		return true;
	}
	else if (t <= flushSecondF + endSecondF) {//表示中
		FontAsset(U"toast" + Format(fontSize))(message).drawAt(pos, ColorF(colorF, 1));
		return true;
	}
	else {//表示し終わり
		FontAsset(U"toast" + Format(fontSize))(message).drawAt(pos, ColorF(colorF, 1 - ((t - (flushSecondF + endSecondF)) / flushSecondF)));
	}

	return t <= (endSecondF + flushSecondF * 2);
}

void MyToast::setMessage(String message) {
	this->message = message;
}