#pragma once
#include "MyRoom.h"
#include "MyKey.h"
#include "User.h"
#include <Siv3D.hpp>
#include "MyRoomSceneBase.h"
#include "TotalPlayTimeTimer.h"
#include "GeneralSoundEffects.h"

class MyRoomReport : public MyRoomSceneBase {
private:
	Audio* backAudio;//BGM
	int age;					//ゲーム内年齢
	String user_name;			//ユーザー名
	float itemAcquisitionRate;	//アイテム取得率
	int gameHighScore[(int)GAME_TYPE::SIZE];	//ゲーム毎ハイスコア
	int gamePlayCount[(int)GAME_TYPE::SIZE];	//ゲーム毎プレイ回数
	String total_play_time;

	float alpha;

	int calcAge();//年齢計算
	void changeAlpha(void);//アルファ値変動

public:
	MyRoomReport(MYROOM_SCENE* scenep);
	~MyRoomReport();
	bool isReady();
	void start();
	void update();
	void draw();
};