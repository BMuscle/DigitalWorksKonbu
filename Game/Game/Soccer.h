#pragma once
#include "MiniGameBase.h"
#include "MySceneManager.h"
#include "SimpleLoadEffect.h"

class Soccer : public MiniGame {
public:
	Soccer(void);
	~Soccer(void);
	bool isReady(void);	//���[�h�I�����Ă��������ǂ���
	void start(void);	//���[�h�󂯂���Ɏ��s��������
	void update(void);	//�v�Z����
	void draw(void);	//�`�揈��
	void outputResult(void);//���ʂ�DB�֏o�͂���
	void restartGame();//�Q�[���ĊJ

private:
	enum SOCCER_SCENE {
		TITLE,
		SELECT_MODE,
		THINKING,
		PRACTICAL_SKILL,
		RESULT,
		INTERRUPTION,

	};
	Audio* backAudio;

	SOCCER_SCENE nowScene, nextScene, oldNowScene;
	int selecttype = 1;//�L�[�p�[���L�b�J�[�����f����֐�
	int inputBotton = 1;
	int conecttingflag = 0;
	int gachasoccer = 0;//�K�`���|�C���g
	int maxpoint = 0;//�ō����_
	int framecount;//�t���[���J�E���g
#define maxaccel 50
#define minaccel -50
	void setNextScene(SOCCER_SCENE next);
	void changeScene();
	void startScene();

	void updateTitle();
	void updateSelect();
	void updateThinking();
	void updatePractical_skill();
	void updateResult();
	void drawTitle();
	void drawSelect();
	void drawThinking();
	void drawPractical_skill();
	void drawResult();
	void stopGame();
	bool whichWin(int);
	void frameCount();//�t���[���J�E���g
	void soccerGachaPoint();//������ۂ���Ƃ�����
	void soccerHighScore(int);//�ō����_
	void itemCheck();//�K�`���A�C�e���`�F�b�N

	SimpleLoadEffect* loadEffect;

};
