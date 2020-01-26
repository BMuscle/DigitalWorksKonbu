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
		BEFORE_THINKING,
		THINKING,
		PRACTICAL_SKILL,
		RESULT,
		INTERRUPTION,

	};
	Audio* backAudio;

	SOCCER_SCENE nowScene, nextScene, oldNowScene;
	int selecttype = 0;//�L�[�p�[���L�b�J�[�����f����֐�
	int inputRBotton = 1;
	int inputUBotton = 1;
	int conecttingflag = 0;
	int gachasoccer = 0;//�K�`���|�C���g
	int maxpoint = 0;//�ō����_
	int framecount;//�t���[���J�E���g
	int coutdown = 240;		//�J�E���g�_�E����3�b�����A�@�b��SHOOT��\�����邽�߁A�v4�b�̃J�E���g�_�E��������
	int countdownflag = 0;
	int thinkdrawflag = 0;
	int shootpower = 0;
	int direction_flag = 0;
	int shootdirection = 0;
	int stopflag = 0;
	int winflag = 0;
	int flykeeper;
	int reactionspeed;
	int soccerboalcount = 120;
	int end_flag = 0;
	int endcount = 0;
	int highshootpower;
	int hightdirection;
	int xplus = 0;
	int xminus = 0;
	int readflag = 0;
#define maxaccel 40
#define minaccel 10
#define gachapo 250//���Q�[�����Ƃ��ɉ��Z�����|�C���g
#define highScorepoint 1000 //�ō����_�̈�ԏ�

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
	void whichWin(int, int);
	void frameCount();//�t���[���J�E���g
	void soccerGachaPoint();//������ۂ���Ƃ�����
	void soccerHighScore(int);//�ō����_
	void itemCheck();//�K�`���A�C�e���`�F�b�N

	void updateBeforeThiking();
	void drawBeforeThiking();

	SimpleLoadEffect* loadEffect;

	bool isStop;

	int acex;

	bool endMusic;

};
