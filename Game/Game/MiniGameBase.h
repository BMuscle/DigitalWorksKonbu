#pragma once
#include "User.h"
#include "MyKey.h"

class MiniGame {
public:
	MiniGame(void) {}
	virtual ~MiniGame(void) {}
	virtual bool isReady(void) = 0;	//���[�h�I�����Ă��������ǂ���
	virtual void start(void) = 0;	//���[�h�󂯂���Ɏ��s��������
	virtual void update(void) = 0;	//�v�Z����
	virtual void draw(void) = 0;	//�`�揈��
	virtual void outputResult(void) = 0;//���ʂ�DB�֏o�͂���
//���������Ȃ��C�����Ă���
};