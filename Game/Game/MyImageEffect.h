#pragma once
#include <Siv3D.hpp>
#include <vector>
#include "EffectInterFace.h"

/*-----------------------------------------------------------------------------------
	�N���X��:MyImageEffect
	�@�@  �\:�A�ԉ摜�̃G�t�F�N�g������
	���@�@��:�G�t�F�N�g�N���X��add���Ďg�p����
-------------------------------------------------------------------------------------*/
class MyImageEffect : public EffectInterFace {
private:
	float switchingTime;	//�摜��؂�ւ��鎞��
	int frameNumber;		//�摜�̖���
	std::vector<TextureRegion> animationTexture;//�A�j���[�V�����p�e�N�X�`���摜�i�؂蕪�����ꂽ��)
public:
	MyImageEffect(String filepath, const int frameX, const int frameY, const float switchingTime = 0.03);
	~MyImageEffect();
	bool update(float t, const Vec2& pos) override;//�I�[�o���C�h�@�v�Z�����@�`�揈�������˂Ă���
	void test() {
		animationTexture.at(4).draw(0,0);
	}
};
