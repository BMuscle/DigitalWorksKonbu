#pragma once
#include "MiniGameBase.h"
#include"DodgeSceneBase.h"
#include"DodgeTitle.h"
#include"DodgeGame.h"
#include"DodgeResult.h"
#include"DodgeHitMotion.h"



class Dodge : public MiniGame {
public:
	Dodge(void);
	~Dodge(void);
	bool isReady(void);	//���[�h�I�����Ă��������ǂ���
	void start(void);	//���[�h�󂯂���Ɏ��s��������
	void update(void);	//�v�Z����
	void draw(void);	//�`�揈��
	void outputResult(void);//���ʂ�DB�֏o�͂���
	void stopGame();	//�Q�[�����ꎞ���f����
	void restartGame();//�Q�[���ĊJ
private:
	DODGE_SCENE nowscene;
	DODGE_SCENE nextscene;
	class DodgeSceneBase* scene;
	void changeScene();
};