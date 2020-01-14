#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "MySqlite3.h"
#include "MyImageButton.h"
#include "TotalPlayTimeTimer.h"
#include "GeneralSoundEffects.h"

constexpr int USER_SIZE = 3;//ユーザの最大数 3

class SelectSaveData : public MyScene {
public:
	SelectSaveData(void);
	~SelectSaveData(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

	int getSelectUser_Id();
private:
	Audio* backAudio;//BGM
	struct Frame{				//セーブデータのフレーム画像
		int id;					//DBのユーザー表の主キー
		String user_name;		//ユーザーの名前
		String total_play_time;	//総プレイ時間
		int x;					//描画座標X
		int y;					//描画座標Y
	};
	int frameCount;				//フレーム数をカウントする
	bool selectDeleteButton;	//削除ボタンを選択しているかどうか
	bool isPopUp;				//ポップアップ表示状態かどうか
	enum POPUP {
		RETURN,
		DECISION,
		SIZE,
		NONE,
	};
	POPUP popUpState;
	MyImageButton* popUpButton[(int)POPUP::SIZE];//左右の戻るボタン決定ボタン

	Frame user_frame[USER_SIZE];//セーブデータのフレーム画像３種
	int selectedUser;			//現在選択されているユーザー(上から0,1,2)
	int selectCountPrev;		//選択された時のフレーム数

	//フレーム数をカウントアップする
	void updateFrameCount();
	//ユーザーの選択状態を更新する(true = 上方向 false = 下方向)
	void rotateSelectedUser(bool isUp = true);
	//セーブデータを削除し、現在の表示をリセットする
	void deleteSaveData();
};

