#pragma once
#include "EffectInterFace.h"
#include <Siv3D.hpp>

/*-----------------------------------------------------------------------------------
	�N���X��:MyToast
	�@�@  �\:�t���b�V�����b�Z�[�W�̃G�t�F�N�g������
	���@�@��:�G�t�F�N�g�N���X��add���Ďg�p����
	���y�ʉ��̂��߂Ƀt�H���g�͓��ꂵ�Ă���B�o�^����΂���قǑ�����̂Œ���
-------------------------------------------------------------------------------------*/
class MyToast : public EffectInterFace {
private:
	String message;
	int fontSize;
	ColorF colorF;
	float endSecondF;	//���b�Z�[�W�\������
	float flushSecondF;	//���b�Z�[�W�����邭�Ȃ�A�Â��Ȃ鎞�̎���

public:
	MyToast(String message, const int fontSize = 70, ColorF colorF = ColorF(0,0,0), const float endSecondF = 1.0, const float flushSecondF = 0.5);
	~MyToast();
	bool update(float t, const Vec2& pos) override;//�I�[�o���C�h�@�v�Z�����@�`�揈�������˂Ă���
	void setMessage(String message);
};
