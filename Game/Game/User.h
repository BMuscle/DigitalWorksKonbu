#pragma once
#include <Siv3D.hpp>
#include "MySqlite3.h"
#include "sqlite3.h"

class User {
private:
	//メンバ変数
	static int user_id;		//ユーザー番号
	static String user_name;	//ユーザーネーム
public:
	User() = delete;
	static void initialize();	//初期化
	static void finalize();		//終了化

	static bool saveDataAccess(int id);//ユーザーデータの選択
	static bool createSaveData(int id, String name);//ユーザーデータの作成

	//ゲッターセッター
	static int getUser_Id();
	static String getUser_Name();



};