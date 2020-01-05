#pragma once
#include "MyRoom.h"
#include "MyKey.h"
#include "User.h"
#include <Siv3D.hpp>
#include "MyRoomSceneBase.h"
#include <vector>
#include <math.h>
/*
メモ　多分棚に置いて見れるように実現する

アクティブにすることで部屋に飾ることが可能？

ちょっと練り直す必要がある。

Collectionテーブルは廃止してアイテムの中に入れる
→ゲームによるアイテムを数個用意するこれはゲーム内で使用することはない。

見れるようにした上で、飾る機能？これはいるのか。
何かデータを取る方がデジタルワークス的には良さげ。
→連携が必要になりめんどくさい。

→棚を置いて見れるように実現
→アイテムテーブルの中身全て置けるようにする。
→機能は時間と相談。

*/

class MyRoomCollection : public MyRoomSceneBase{
private:
	CSVData csvItem[(int)GAME_TYPE::SIZE];
	MyImageButton* button;

	bool isButtonSelect;		//戻るボタンの選択状態

	bool isCollectionSelected;	//コレクションを選択状態かどうか

	bool hasItem;				//アイテムを１つでも保持しているかどうか

	std::vector<int> itemVec[(int)GAME_TYPE::SIZE];//アイテムの座標を保持

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

public:
	MyRoomCollection(MYROOM_SCENE* scenep);
	~MyRoomCollection();
	bool isReady();
	void start();
	void update();
	void draw();
};