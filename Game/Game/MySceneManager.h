#pragma once
#include "MyScene.h"
#include "LoadEffect.h"
#include "Title.h"
#include "SelectSaveData.h"
#include "CreateSaveData.h"
#include "SelectMode.h"
#include "Game.h"
#include "MyRoom.h"
#include "Gacha.h"

enum class SCENE {//�V�[���̎��
	TITLE,
	SELECT_SAVEDATA,
	CREATE_SAVEDATA,
	SELECT_MODE,
	GAME,
	MYROOM,
	GACHA,
	NONE
};

class MySceneManager {
public:
	MySceneManager() = delete;
	//������
	static void initialize();	
	//�I����
	static void finalize();		
	//�V�[���̌v�Z����
	static void updateScene();	
	//�V�[���̕`�揈��
	static void drawScene();	
	//�V�[���̕ύX�v���i���t���[���ŃV�[�����ڍs����)
	static void setNextScene(SCENE next);
private:
	static LoadEffect* loadEffect;//���[�h�G�t�F�N�g
	static bool isLoadFinished;//���[�h���������Ă��邩�t���O
	static MyScene* scene;		//���ݎ��s����Scene
	static SCENE NOWSCENE;		//���ݎ��s����SCENE
	static SCENE NEXTSCENE;		//�V�[���ڍs���ɂ�NONE�ȊO������
	static void changeScene();	//�V�[���ڍs
	
};
