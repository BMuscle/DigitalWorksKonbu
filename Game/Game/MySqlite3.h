#pragma once
#include "sqlite3.h"
#include <Siv3D.hpp>

class MySqlite3 {
private:
	static sqlite3* db;//データベースへのポインタ

	//ゲームデータ投入
	static void insertGames();
	//アイテムとユーザーアイテムデータ投入
	static void insertItems();

public:
	MySqlite3() = delete;
	static bool initialize();	//初期化 DBの初期化を行う
	static bool finalize();		//終了化
	static bool DBCREATE();		//基本使用しない　データベースの初期設定を行う。 DBファイル消してから実行
	static sqlite3* getDB();//データベースへのポインタを参照する

};