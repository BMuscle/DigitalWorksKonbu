#pragma once
#include "MiniGameBase.h"

class Soccer : public MiniGame {
public:
	Soccer(void);
	~Soccer(void);
	bool isReady(void);	//���[�h�I�����Ă��������ǂ���
	void start(void);	//���[�h�󂯂���Ɏ��s��������
	void update(void);	//�v�Z����
	void draw(void);	//�`�揈��
	void outputResult(void);//���ʂ�DB�֏o�͂���

private:
	Audio* backAudio;
};