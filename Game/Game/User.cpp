#include "User.h"


int User::user_id;						//ユーザー番号	
String User::user_name;					//ユーザーネーム
int User::user_point;					//現在の所持ポイント
int64 User::user_total_play_time;		//総プレイ時間[s]
String User::user_play_start_date;		//プレイ開始日
std::map<int, bool> User::Items[(int)GAME_TYPE::SIZE];//ユーザーが持っているアイテム一覧

void User::initialize() {	//初期化

}
void User::finalize() {		//終了化

}

bool User::simpleSaveDataAccess(int id, String& name, int64& total_play_time) {
	//一旦初期化
	name = U"";
	total_play_time = 0;
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT name, total_play_time FROM Users WHERE id = ?;";

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, id);//1つ目の？をidにする
	if (err != SQLITE_OK) {
		//エラー処理
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			std::string str((char*)sqlite3_column_text(stmt, 0));//0列目（名前をUTF-8で受け取りUTF32に変換する)
			name = Unicode::FromUTF8(str);
			total_play_time = sqlite3_column_int64(stmt, 1);//1列目 (プレイ時間の取得)
		}
		if (err != SQLITE_DONE) {
			//データが正しく取得できなかった場合
		}
	}
	//ステートメントの解放
	sqlite3_finalize(stmt);
	return true;
}

bool User::saveDataAccess(int id) {//idに対応するセーブデータを保存する
	user_id = id;
	if (selectUser(id)) {
		if (selectUserItems(id)) {
			return true;
		}
	}
	return false;
}

bool User::createSaveData(int id, String name) {//ユーザーデータ作成
	std::string ENname = name.toUTF8();//エンコード済みの名前 UTF-32→UTF-8で保存する
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	//----------ユーザーデータ更新-----------
	//SQLバインド用
	std::string sql = "UPDATE Users SET name = ?, play_start_date = date('now')"
		"WHERE id = ?;";

	//ステートメント作成
	sqlite3_prepare_v2(MySqlite3::getDB(),sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	//ステートハンドラ一旦初期化
	sqlite3_reset(stmt);
	//バインド
	sqlite3_bind_text(stmt, 1, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);//1つ目の？をnameにする
	sqlite3_bind_int(stmt, 2, id);//2つ目の？をidにする
	sqlite3_step(stmt);//SQL実行
	sqlite3_finalize(stmt);//ステートメント消去

	//ここでユーザーデータを取得させる
	saveDataAccess(id);
	return true;
}

int User::getSaveDataSize() {//空きセーブデータのidを昇順に取得する無ければ0
	int id = 0;//返すidの初期化
	int err;//エラーコードが入る
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT COUNT(*) FROM Users WHERE name != '';";

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	if (err != SQLITE_OK) {
		//エラー処理
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			id = sqlite3_column_int(stmt, 0);//0列目 idの取得
		}
		if (err != SQLITE_DONE) {
			//データが正しく取得できなかった場合
			id = 0;
		}
	}
	//ステートメントの解放
	sqlite3_finalize(stmt);
	return id;
}


bool User::selectUser(int id) {//ユーザーのデータを変数に格納する
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT name, point, total_play_time, play_start_date FROM Users WHERE id = ?;";

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, id);//1つ目の？をidにする
	if (err != SQLITE_OK) {
		//エラー処理
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			std::string str((char*)sqlite3_column_text(stmt, 0));//0列目（名前をUTF-8で受け取りUTF32に変換する)
			user_name = Unicode::FromUTF8(str);
			user_point = sqlite3_column_int(stmt, 1);//1列目 (ポイントの取得)
			user_total_play_time = sqlite3_column_int64(stmt, 2);//1列目 (プレイ時間の取得)
			str = std::string((char*)sqlite3_column_text(stmt, 3));//3列目(プレイ開始日をUTF-8で受け取りUTF32に変換する)
			user_play_start_date = Unicode::FromUTF8(str);
		}
		if (err != SQLITE_DONE) {
			//データが正しく取得できなかった場合
			sqlite3_finalize(stmt);//ステートメントの解放
			return false;
		}
	}
	//ステートメントの解放
	sqlite3_finalize(stmt);
	return true;
}
bool User::selectUserItems(int id) {//ユーザーアイテムデータを変数に格納する
	for (int game_id = 0; game_id < (int)GAME_TYPE::SIZE; game_id++) {
		//変数宣言
		int err;
		sqlite3_stmt* stmt = NULL;//ステートメントハンドル
		const char* pzTest;
		std::string sql = "SELECT Items.key, UserItems.flag FROM UserItems, Items WHERE UserItems.item_id = Items.id AND UserItems.user_id = ? AND Items.game_id = ?;";

		//ステートメント作成
		err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		sqlite3_bind_int(stmt, 1, id);//1つ目の？をidにする
		sqlite3_bind_int(stmt, 2, game_id + 1);//2つ目の？をgame_idにする
		if (err != SQLITE_OK) {
			//エラー処理
			return false;
		}
		else {
			//データの抽出
			while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
				int i = sqlite3_column_int(stmt, 0);//0列目 (idの取得)
				bool f = sqlite3_column_int(stmt, 1);//1列目 (flagの取得)
				Items[game_id][i] = f;//マップへデータの追加
			}
			if (err != SQLITE_DONE) {
				//データが正しく取得できなかった場合
				sqlite3_finalize(stmt);//ステートメントの解放
				return false;
			}
		}
		//ステートメントの解放
		sqlite3_finalize(stmt);
	}
	return true;
}

//ユーザIDの取得
int User::getUser_Id() {
	return user_id;
}
//ユーザーネームの取得
String User::getUser_Name() {
	return user_name;
}
//ユーザーがアイテムを持っているかどうかtrue falseで返す
bool User::getHasItems(GAME_TYPE type, int key) {
	return Items[((int)type) + 1][key];
}