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
	return Items[((int)type)][key];
}

//ガチャ用 取得できるアイテムが存在するかどうか
bool User::hasAllItem() {
	for (int i = 0; i < (int)GAME_TYPE::SIZE; i++) {
		for (const auto& [key, flag] : Items[i]) {
			if (!flag) {
				return false;//falseが見つかれば持っていないアイテムが存在する
			}
		}
	}
	return true;
}

//ガチャ
bool User::getRandomGacha(String& itemName, int& key, GAME_TYPE& type) {
	if (hasAllItem()) { return false; }//アイテムを全て持っているのでガチャ出来ない
	struct ItemPack {
		GAME_TYPE type;
		int key;
	} ;

	std::vector<ItemPack> possible;

	for (int i = 0; i < (int)GAME_TYPE::SIZE; i++) {
		for (const auto& [key, flag] : Items[i]) {
			if (!flag) {
				ItemPack tmp;
				tmp.key = key;
				tmp.type = (GAME_TYPE)i;
				possible.push_back(tmp);
			}
		}
	}

	// シャッフル
	std::mt19937_64 get_rand_mt;
	std::shuffle(possible.begin(), possible.end(), get_rand_mt);

	// アイテム格納
	type = possible.begin()->type;
	key = possible.begin()->key;
	itemName = getItemName((int)possible.begin()->type + 1, possible.begin()->key);
	setUserItem((int)possible.begin()->type + 1, possible.begin()->key);
	Items[(int)possible.begin()->type].at(possible.begin()->key) = true;

	return true;
}

String User::getItemName(int game_id, int key){
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT Items.name FROM Items WHERE Items.game_id = ? AND Items.key = ?;";
	String name;

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, game_id);//1つ目の？をidにする
	sqlite3_bind_int(stmt, 2, key);//2つ目の？をgame_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			std::string str((char*)sqlite3_column_text(stmt, 0));//0列目（名前をUTF-8で受け取りUTF32に変換する)
			name = Unicode::FromUTF8(str);
		}
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);

	return name;
}

void User::setUserItem(int game_id, int key) {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "UPDATE UserItems SET flag = 1 WHERE user_id = ? AND item_id = ?;";

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, user_id);//1つ目の？をuser_idにする
	sqlite3_bind_int(stmt, 2, getItemId(game_id, key));//2つ目の？をitem_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return;
	}
	else {
		sqlite3_step(stmt);
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);

}

int User::getItemId(int game_id, int key) {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT Items.id FROM Items WHERE Items.game_id = ? AND Items.key = ?;";
	int item_id = 0;

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, game_id);//1つ目の？をidにする
	sqlite3_bind_int(stmt, 2, key);//2つ目の？をgame_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			item_id = sqlite3_column_int(stmt, 0);
		}
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);

	return item_id;
}

//ポイントの加算
bool User::addUserPoint(int addPoint) {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "UPDATE Users SET point = ? WHERE id = ?";

	user_point += addPoint;
	if (user_point >= 100000) {
		user_point = 99999;
	}
	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, user_point);//1つ目の？をpointにする
	sqlite3_bind_int(stmt, 2, user_id);//2つ目の？をuser_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);
	return true;
}
//ポイントの減算
bool User::subUserPoint(int subPoint) {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "UPDATE Users SET point = ? WHERE id = ?";

	user_point -= subPoint;
	if (user_point < 0) {
		user_point = 0;
	}
	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, user_point);//1つ目の？をpointにする
	sqlite3_bind_int(stmt, 2, user_id);//2つ目の？をuser_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);
	return true;
}
int User::getUserPoint() {
	return user_point;
}


bool User::setTotalPlayTime() {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "UPDATE Users SET total_play_time = ? WHERE id = ?";

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int64(stmt, 1, user_total_play_time + TotalPlayTimeTimer::getSecond());//1つ目の？をpointにする
	sqlite3_bind_int(stmt, 2, user_id);//2つ目の？をuser_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);
	return true;
}

bool User::addGameScore(GAME_TYPE type, int score) {
	if (score < 0 || score > 100) { return false; }
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "INSERT INTO GameScores(user_id, game_id, score1, play_date) VALUES(?, ?, ?, date('now'));";

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1つ目の？をuser_idにする
	sqlite3_bind_int(stmt, 2, (int)type + 1);//2つ目の？をgame_idにする
	sqlite3_bind_int(stmt, 3, score);//3つ目の？をscoreにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);
	return true;
}

int User::getGameHighScore(GAME_TYPE type) {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT MAX(score1) FROM GameScores WHERE user_id = ? AND game_id = ?;";
	int highScore = 0;

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1つ目の？をidにする
	sqlite3_bind_int(stmt, 2, (int)type + 1);//2つ目の？をgame_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return 0;
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			highScore = sqlite3_column_int(stmt, 0);
		}
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);

	return highScore;
}


int User::getGamePlayCount(GAME_TYPE type) {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT COUNT(*) FROM GameScores WHERE user_id = ? AND game_id = ?;";
	int playCount = 0;

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1つ目の？をidにする
	sqlite3_bind_int(stmt, 2, (int)type + 1);//2つ目の？をgame_idにする
	if (err != SQLITE_OK) {
		//エラー処理
		return 0;
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			playCount = sqlite3_column_int(stmt, 0);
		}
	}

	//ステートメントの解放
	sqlite3_finalize(stmt);

	return playCount;
}

float User::getItemAcquisitionRate() {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT COUNT(*) FROM UserItems WHERE user_id = ?;";
	int allRows = 0;

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1つ目の？をidにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			allRows = sqlite3_column_int(stmt, 0);
		}
	}
	//ステートメントの解放
	sqlite3_finalize(stmt);


	//変数初期化
	err = 0;
	stmt = NULL;//ステートメントハンドル
	pzTest = NULL;
	sql = "SELECT COUNT(*) FROM UserItems WHERE user_id = ? AND flag = 1;";
	int trueRows = 0;

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1つ目の？をidにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			trueRows = sqlite3_column_int(stmt, 0);
		}
	}
	//ステートメントの解放
	sqlite3_finalize(stmt);
	if (allRows == 0) {
		return 0;
	}
	return (float)trueRows / allRows;
}

String User::getTotalPlayTime() {
	//変数宣言
	int err;
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	std::string sql = "SELECT total_play_time FROM Users WHERE id = ?;";

	int64 total_play_time = 0;

	//ステートメント作成
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1つ目の？をidにする
	if (err != SQLITE_OK) {
		//エラー処理
		return false;
	}
	else {
		//データの抽出
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			total_play_time = sqlite3_column_int64(stmt, 0);
		}
	}
	//ステートメントの解放
	sqlite3_finalize(stmt);

	//現在のプレイ時間を足す
	total_play_time += TotalPlayTimeTimer::getSecond();

	String playTimeStr = U"";
	if (total_play_time / 3600 > 0) {
		playTimeStr = playTimeStr + Format((int)total_play_time / 3600) + U"時間";
		total_play_time %= 3600;
	}
	
	if (total_play_time / 60 > 0) {
		playTimeStr = playTimeStr + Format((int)total_play_time / 60) + U"分";
		total_play_time %= 60;
	}
	else {
		playTimeStr = playTimeStr + U"0分";
	}
	return playTimeStr;
}