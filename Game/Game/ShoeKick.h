#pragma once
#include "MiniGameBase.h"
#include <Siv3D.hpp>

class ShoeKick : public MiniGame {
public:
	ShoeKick(void);
	~ShoeKick(void);
	bool isReady(void);	//���[�h�I�����Ă��������ǂ���
	void start(void);	//���[�h�󂯂���Ɏ��s��������
	void update(void);	//�v�Z����
	void draw(void);	//�`�揈��
	void outputResult(void);//���ʂ�DB�֏o�͂���

private:
	Audio* backAudio;



	//�V�[���ύX�p
	enum SCENE {
		TITLE,
		KICK,
		FLY,
		FALL,
		RESULT,
	};
	SCENE nowScene, nextScene;
	void changeScene();
	void setNextScene(SCENE next);

	//�R��V�[���̕ϐ�
	int countDown;

	//�`��
	void scenedraw(void);
};