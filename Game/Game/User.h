#pragma once
#include <Siv3D.hpp>

class User {
private:
	//メンバ変数
	static int user_id;		//ユーザー番号
	static String user_name;	//ユーザーネーム
public:
	User() = delete;
	static void initialize();	//初期化
	static void finalize();		//終了化

	static bool saveDataAccess(int id);
	static bool createSaveData(int id, String name);

	//ゲッターセッター
	static int getUser_Id();
	static String getUser_Name();



};