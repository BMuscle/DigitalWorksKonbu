#pragma once
#include <Siv3D.hpp>
#include "MySqlite3.h"
#include "sqlite3.h"

class User {
private:
	//メンバ変数
	static int user_id;	//ユーザー番号	
	static String user_name;	//ユーザーネーム
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



};