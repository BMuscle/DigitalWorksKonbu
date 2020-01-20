#pragma once
#include "MyRoom.h"
#include "MyKey.h"
#include "User.h"
#include <Siv3D.hpp>
#include "MyRoomSceneBase.h"
#include <vector>
#include <math.h>
#include "GeneralSoundEffects.h"

class MyRoomCollection : public MyRoomSceneBase{
private:
	CSVData csvItem[(int)GAME_TYPE::SIZE];
	MyImageButton* button;

	Audio* backAudio;	//BGM

	bool isButtonSelect;		//戻るボタンの選択状態

	bool isCollectionSelected;	//コレクションを選択状態かどうか

	bool hasItem;				//アイテムを１つでも保持しているかどうか

	std::vector<int> itemVec[(int)GAME_TYPE::SIZE];//アイテムの座標を保持

	float alpha;

	//棚の行列を保持
	struct CollectionTable {
		int row;		
		int column;
	} selectedItem;

	//棚の行列の初期化
	void initializeCollectionTable();

	void selectedItemTextLoad();

	//棚の行を移動する 移動できる時0以上の値の列が返る。　移動できない時 -1が返る
	int selectedMoveRow(int row);

	void changeAlpha(void);//アルファ値変動

	void deci2Play();
public:
	MyRoomCollection(MYROOM_SCENE* scenep);
	~MyRoomCollection();
	bool isReady();
	void start();
	void update();
	void draw();
};