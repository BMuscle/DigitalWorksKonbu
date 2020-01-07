#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "MyImageButton.h"
#include "MyImageEffect.h"
#include "MyEffects.h"
#include "MyToast.h"
#include "SimpleLoadEffect.h"
#include "GachaItemDescription.h"
#include "GeneralSoundEffects.h"

//���Ԃ�����΃��t�@�N�^�����O�i�N���X�����j

class Gacha : public MyScene {
public:
	Gacha(void);
	~Gacha(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;	//BGM

	SimpleLoadEffect* simpleLoadEffect;

	enum class GACHA_STATE {//�K�`���̏�Ԃ�\��
		TITLE,
		EFFECT,
		RESULT,
		END,

	};

	GACHA_STATE nowGachaState;	//���݂̃K�`���̏��
	GACHA_STATE nextGachaState;	//�ڍs�������K�`���̏��

	MyEffects* effects;//�K�`���G�t�F�N�g�ȊO�̃G�t�F�N�g�Ǘ�(�����I�ɕ������̂̓G�t�F�N�g�̏I���������~������������j
	MyToast* toast;//�g�[�X�g���b�Z�[�W�G�t�F�N�g

	MyEffects* gachaEffects;	//�K�`���G�t�F�N�g�Ǘ��p
	MyImageEffect* gachaEffect;	//�K�`�����񂵂Ă���摜�G�t�F�N�g �摜���傫���̂łQ���ɕ���



	enum class BUTTON {//�{�^���̎��
		GACHA,
		EXIT,
		SIZE,
	};
	MyImageButton* button[(int)BUTTON::SIZE];	//�摜�{�^���N���X
	BUTTON selectedButton;						//���ݑI������Ă���{�^��

	String itemName;//�K�`���Ŏ擾�����A�C�e���̖��O

	//���ݑI������Ă�����̂̍X�V����
	void selectedMove();

	//�{�^���̕`�揈��
	void drawButton();

	//�K�`���̏�Ԉڍs�v��������
	void setNextGachaState(GACHA_STATE nextState);

	//�K�`���̏�ԗv���ɉ����ĕύX����
	void changeNextGachaState();

	//���邭�Ȃ�n�߂鎞�Ɏ��s����
	void loadBrightingFunc();

	//���[�h���I��������Ɏ��s����
	void loadEndFunc();

	//�K�`���^�C�g����ʂ̌v�Z����
	void updateTitle();

	//�K�`�����o���邩�ǂ�����check �G���[���������̒���
	bool isPlayGacha();

	//�K�`�����s��
	void randomGacha();

	//�K�`�����ʂ̕`��
	void resultDraw();
};
