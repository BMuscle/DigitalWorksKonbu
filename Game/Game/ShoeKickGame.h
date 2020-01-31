#pragma once

#include <Siv3D.hpp>
#include "MySceneManager.h"
#include "ShoeKickSceneBase.h"
#include "GeneralSoundEffects.h"
#include <math.h>
#include "ShoeCharacter.h"
#include "Shoe.h"
#include "ShoeGage.h"

//�K�`���A�C�e���p �L�[�l�́{1
enum class GACHA_ITEM {
	SPORTS_SHOE,
	ROCKET_BOOSTER,
	WING,
	ROLLER,
	CAT,
	SIZE,
};
#define GROUND Scene::Height() * 0.8

class ShoeKickGame : public ShoeKickSceneBase {
private:

	//�擾���Ă���A�C�e��
	Array<bool> hasItems;

	//���ʕ����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�ϐ��錾
	bool isStart;

	Audio* backAudio;

	bool isDescription;//�����\���t���O

	class ShoeCharacter* character;
	class Shoe* shoe;
	class ShoeGage* shoeGage;

	enum GAME_STATE {
		KICK,
		FLY,
		END,
	};

	GAME_STATE nowGameState;
	GAME_STATE nextGameState;

	int frameCnt;

	float kickPower;	//�Z���T�[�f�[�^�̍ő�l�����

	typedef struct _SignBoard {
		Vec2 vec;
		int meter;
	}SignBoard;

	std::vector<SignBoard> boardVec;

	//�֐��錾

	void setNextState(GAME_STATE next);
	void changeState();

	void updateKick();
	void drawKick();

	void updateFly();
	void drawFly();

	SignBoard createSignBoard(int meter);

	//KICK�̏����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�ϐ��錾
	int kickCount;//�R��܂ł̃J�E���g

	Texture* countTexture[4];

	//�֐��錾

	//�R�鎞�̃J�E���g�_�E��
	void updateKickTimer();
	//�R�鎞�̃J�E���g�_�E���`��
	void drawKickTimer();

	void setKickTimer(int kicktime);


	//FLY�̏����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//���W�͒��S���瓮�������A�ړ������ɉ����Ĕw�i�𓮂���


public:
	ShoeKickGame(SHOEKICK_SCENE* scenep);
	~ShoeKickGame();

	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

	int getMeter();
};
