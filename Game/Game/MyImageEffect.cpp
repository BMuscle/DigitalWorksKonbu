#include "MyImageEffect.h"

MyImageEffect::MyImageEffect(String filepath, const int frameX, const int frameY, const float switchingTime) {
	this->switchingTime = switchingTime;//�ؑ֎��Ԋi�[
	this->frameNumber = frameX * frameY;//�t���[�������i�[
	Image baseTexture = Image(filepath);
	for (int y = 0; y < baseTexture.height(); y += (baseTexture.height() / frameY)) {
		for (int x = 0; x < baseTexture.width(); x += (baseTexture.width() / frameX)) {
			animationTexture.push_back(Texture(baseTexture.clipped(x, y, (baseTexture.width() / frameX), (baseTexture.height() / frameY))));
		}
	}
	baseTexture.release();//���摜���J��
}
MyImageEffect::~MyImageEffect() {

}
bool MyImageEffect::update(float t, const Vec2& pos) {//�I�[�o���C�h�@�v�Z�����@�`�揈�������˂Ă���
	if (t / switchingTime >= animationTexture.size()) {
		animationTexture.at(animationTexture.size() - 1).drawAt(pos);//���Ԃɕ`�悷��
		return false;//�`��I��
	}
	animationTexture.at(t / switchingTime).drawAt(pos);//���Ԃɕ`�悷��
	return t < (switchingTime * frameNumber);//�t���[����S�ĕ`�悵�I�����false��Ԃ�
}
