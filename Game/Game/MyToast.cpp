#include "MyToast.h"

MyToast::MyToast(String message, const int fontSize, ColorF colorF, const float endSecondF, const float flushSecondF) {
	this->message = message;
	this->fontSize = fontSize;
	this->colorF = colorF;
	this->endSecondF = endSecondF;
	this->flushSecondF = flushSecondF;
	if (!FontAsset::IsRegistered(U"toast" + Format(fontSize))) {//�t�H���g���o�^����Ă��Ȃ�
		FontAsset::Register(U"toast" + Format(fontSize), fontSize);
		FontAsset::Preload(U"toast" + Format(fontSize));
	}
	
}
MyToast::~MyToast() {

}
bool MyToast::update(float t, const Vec2& pos) {//�I�[�o���C�h�@�v�Z�����@�`�揈�������˂Ă���
	if (t <= flushSecondF) {//�\�����n��
		FontAsset(U"toast" + Format(fontSize))(message).drawAt(pos, ColorF(colorF, t / flushSecondF));
		return true;
	}
	else if (t <= flushSecondF + endSecondF) {//�\����
		FontAsset(U"toast" + Format(fontSize))(message).drawAt(pos, ColorF(colorF, 1));
		return true;
	}
	else {//�\�����I���
		FontAsset(U"toast" + Format(fontSize))(message).drawAt(pos, ColorF(colorF, 1 - ((t - (flushSecondF + endSecondF)) / flushSecondF)));
	}

	return t <= (endSecondF + flushSecondF * 2);
}

void MyToast::setMessage(String message) {
	this->message = message;
}