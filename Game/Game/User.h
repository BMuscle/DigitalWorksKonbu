#pragma once
#include <Siv3D.hpp>
#include "MySqlite3.h"
#include "sqlite3.h"
#include <map>

enum class GAME_TYPE {//データベースに入ってる値は＋１
	SOCCER = 0,
	SHOEKICK = 1,
	DODGE = 2,
	SIZE = 3,
};

class User {
private:
	//メンバ変数
	static int user_id;						//ユーザー番号	
	static String user_name;				//ユーザーネーム
	static int user_point;					//現在の所持ポイント
	static int64 user_total_play_time;		//総プレイ時間[s]
	static String user_play_start_date;		//プレイ開始日




	static std::map<int, bool> Items[(int)GAME_TYPE::SIZE];//ユーザーが持っているアイテム一覧

	static bool selectUser(int id);//ユーザーのデータを変数に格納する
	static bool selectUserItems(int id);//ユーザーアイテムデータを変数に格納する

public:
	User() = delete;
	//初期化
	static void initialize();	
	//終了化
	static void finalize();		
	//簡単なユーザーデータへのアクセス、使用目的は選択するときの簡易表示用
	static bool simpleSaveDataAccess(int id, String& name, int64& total_play_time);
	//ユーザーデータの選択 自クラスの変数に保存する
	static bool saveDataAccess(int id);
	//ユーザーデータの作成
	static bool createSaveData(int id, String name);
	//セーブデータの存在する数を返す
	static int getSaveDataSize();

	//ゲッターセッター
	//ユーザIDの取得
	static int getUser_Id();
	//ユーザーネームの取得
	static String getUser_Name();
	//ユーザーがアイテムを持っているかどうかtrue falseで返す
	static bool getHasItems(GAME_TYPE type, int key);



};