#pragma once
#include "MyScene.h"
#include "LoadEffect.h"
#include "Title.h"
#include "SelectSaveData.h"
#include "CreateSaveData.h"
#include "SelectMode.h"
#include "Game.h"
#include "MyRoom.h"

enum class SCENE {
	TITLE,
	SELECT_SAVEDATA,
	CREATE_SAVEDATA,
	SELECT_MODE,
	GAME,
	MYROOM,
	NONE
};

class MySceneManager {
public:
	MySceneManager() = delete;
	static void initialize();	//������
	static void finalize();		//�I����

	static void updateScene();	//�V�[���̌v�Z����
	static void drawScene();	//�V�[���̕`�揈��
	static void setNextScene(SCENE next);//���t���[���ɂăV�[�����ڍs����
private:
	static LoadEffect* loadEffect;
	static MyScene* scene;		//���ݎ��s����Scene
	static SCENE NOWSCENE;		//���ݎ��s����SCENE
	static SCENE NEXTSCENE;		//�V�[���ڍs���ɂ�NONE�ȊO������
	static void changeScene();	//�V�[���ڍs
	static bool isLoadFinished;	
};
