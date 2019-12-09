#pragma once
#include "MyScene.h"
#include "Title.h"
#include "LoadEffect.h"

enum class SCENE {
	TITLE,
	SYNCRC,
	GAME,
	RESULT,
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
