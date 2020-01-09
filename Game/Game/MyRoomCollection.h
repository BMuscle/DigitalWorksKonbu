#pragma once
#include "MyRoom.h"
#include "MyKey.h"
#include "User.h"
#include <Siv3D.hpp>
#include "MyRoomSceneBase.h"
#include <vector>
#include <math.h>

class MyRoomCollection : public MyRoomSceneBase{
private:
	CSVData csvItem[(int)GAME_TYPE::SIZE];
	MyImageButton* button;

	bool isButtonSelect;		//�߂�{�^���̑I�����

	bool isCollectionSelected;	//�R���N�V������I����Ԃ��ǂ���

	bool hasItem;				//�A�C�e�����P�ł��ێ����Ă��邩�ǂ���

	std::vector<int> itemVec[(int)GAME_TYPE::SIZE];//�A�C�e���̍��W��ێ�

	//�I�̍s���ێ�
	struct CollectionTable {
		int row;		
		int column;
	} selectedItem;

	//�I�̍s��̏�����
	void initializeCollectionTable();

	void selectedItemTextLoad();

	//�I�̍s���ړ����� �ړ��ł��鎞0�ȏ�̒l�̗񂪕Ԃ�B�@�ړ��ł��Ȃ��� -1���Ԃ�
	int selectedMoveRow(int row);

public:
	MyRoomCollection(MYROOM_SCENE* scenep);
	~MyRoomCollection();
	bool isReady();
	void start();
	void update();
	void draw();
};