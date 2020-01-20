#include "User.h"


int User::user_id;						//���[�U�[�ԍ�	
String User::user_name;					//���[�U�[�l�[��
int User::user_point;					//���݂̏����|�C���g
int64 User::user_total_play_time;		//���v���C����[s]
String User::user_play_start_date;		//�v���C�J�n��
std::map<int, bool> User::Items[(int)GAME_TYPE::SIZE];//���[�U�[�������Ă���A�C�e���ꗗ

void User::initialize() {	//������

}
void User::finalize() {		//�I����

}

bool User::simpleSaveDataAccess(int id, String& name, int64& total_play_time) {
	//��U������
	name = U"";
	total_play_time = 0;
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT name, total_play_time FROM Users WHERE id = ?;";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, id);//1�ڂ́H��id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			std::string str((char*)sqlite3_column_text(stmt, 0));//0��ځi���O��UTF-8�Ŏ󂯎��UTF32�ɕϊ�����)
			name = Unicode::FromUTF8(str);
			total_play_time = sqlite3_column_int64(stmt, 1);//1��� (�v���C���Ԃ̎擾)
		}
		if (err != SQLITE_DONE) {
			//�f�[�^���������擾�ł��Ȃ������ꍇ
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return true;
}

bool User::saveDataAccess(int id) {//id�ɑΉ�����Z�[�u�f�[�^��ۑ�����
	user_id = id;
	if (selectUser(id)) {
		if (selectUserItems(id)) {
			return true;
		}
	}
	return false;
}

bool User::createSaveData(int id, String name) {//���[�U�[�f�[�^�쐬
	std::string ENname = name.toUTF8();//�G���R�[�h�ς݂̖��O UTF-32��UTF-8�ŕۑ�����
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	//----------���[�U�[�f�[�^�X�V-----------
	//SQL�o�C���h�p
	std::string sql = "UPDATE Users SET name = ?, play_start_date = date('now')"
		"WHERE id = ?;";

	//�X�e�[�g�����g�쐬
	sqlite3_prepare_v2(MySqlite3::getDB(),sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	//�X�e�[�g�n���h����U������
	sqlite3_reset(stmt);
	//�o�C���h
	sqlite3_bind_text(stmt, 1, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);//1�ڂ́H��name�ɂ���
	sqlite3_bind_int(stmt, 2, id);//2�ڂ́H��id�ɂ���
	sqlite3_step(stmt);//SQL���s
	sqlite3_finalize(stmt);//�X�e�[�g�����g����

	//�����Ń��[�U�[�f�[�^���擾������
	saveDataAccess(id);
	return true;
}

int User::getSaveDataSize() {//�󂫃Z�[�u�f�[�^��id�������Ɏ擾���閳�����0
	int id = 0;//�Ԃ�id�̏�����
	int err;//�G���[�R�[�h������
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT COUNT(*) FROM Users WHERE name != '';";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	if (err != SQLITE_OK) {
		//�G���[����
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			id = sqlite3_column_int(stmt, 0);//0��� id�̎擾
		}
		if (err != SQLITE_DONE) {
			//�f�[�^���������擾�ł��Ȃ������ꍇ
			id = 0;
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return id;
}


bool User::selectUser(int id) {//���[�U�[�̃f�[�^��ϐ��Ɋi�[����
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT name, point, total_play_time, play_start_date FROM Users WHERE id = ?;";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, id);//1�ڂ́H��id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			std::string str((char*)sqlite3_column_text(stmt, 0));//0��ځi���O��UTF-8�Ŏ󂯎��UTF32�ɕϊ�����)
			user_name = Unicode::FromUTF8(str);
			user_point = sqlite3_column_int(stmt, 1);//1��� (�|�C���g�̎擾)
			user_total_play_time = sqlite3_column_int64(stmt, 2);//1��� (�v���C���Ԃ̎擾)
			str = std::string((char*)sqlite3_column_text(stmt, 3));//3���(�v���C�J�n����UTF-8�Ŏ󂯎��UTF32�ɕϊ�����)
			user_play_start_date = Unicode::FromUTF8(str);
		}
		if (err != SQLITE_DONE) {
			//�f�[�^���������擾�ł��Ȃ������ꍇ
			sqlite3_finalize(stmt);//�X�e�[�g�����g�̉��
			return false;
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return true;
}
bool User::selectUserItems(int id) {//���[�U�[�A�C�e���f�[�^��ϐ��Ɋi�[����
	for (int game_id = 0; game_id < (int)GAME_TYPE::SIZE; game_id++) {
		//�ϐ��錾
		int err;
		sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
		const char* pzTest;
		std::string sql = "SELECT Items.key, UserItems.flag FROM UserItems, Items WHERE UserItems.item_id = Items.id AND UserItems.user_id = ? AND Items.game_id = ?;";

		//�X�e�[�g�����g�쐬
		err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		sqlite3_bind_int(stmt, 1, id);//1�ڂ́H��id�ɂ���
		sqlite3_bind_int(stmt, 2, game_id + 1);//2�ڂ́H��game_id�ɂ���
		if (err != SQLITE_OK) {
			//�G���[����
			return false;
		}
		else {
			//�f�[�^�̒��o
			while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
				int i = sqlite3_column_int(stmt, 0);//0��� (id�̎擾)
				bool f = sqlite3_column_int(stmt, 1);//1��� (flag�̎擾)
				Items[game_id][i] = f;//�}�b�v�փf�[�^�̒ǉ�
			}
			if (err != SQLITE_DONE) {
				//�f�[�^���������擾�ł��Ȃ������ꍇ
				sqlite3_finalize(stmt);//�X�e�[�g�����g�̉��
				return false;
			}
		}
		//�X�e�[�g�����g�̉��
		sqlite3_finalize(stmt);
	}
	return true;
}

//���[�UID�̎擾
int User::getUser_Id() {
	return user_id;
}
//���[�U�[�l�[���̎擾
String User::getUser_Name() {
	return user_name;
}
//���[�U�[���A�C�e���������Ă��邩�ǂ���true false�ŕԂ�
bool User::getHasItems(GAME_TYPE type, int key) {
	return Items[((int)type)][key];
}

//�K�`���p �擾�ł���A�C�e�������݂��邩�ǂ���
bool User::hasAllItem() {
	for (int i = 0; i < (int)GAME_TYPE::SIZE; i++) {
		for (const auto& [key, flag] : Items[i]) {
			if (!flag) {
				return false;//false��������Ύ����Ă��Ȃ��A�C�e�������݂���
			}
		}
	}
	return true;
}

//�K�`��
bool User::getRandomGacha(String& itemName, int& key, GAME_TYPE& type) {
	if (hasAllItem()) { return false; }//�A�C�e����S�Ď����Ă���̂ŃK�`���o���Ȃ�
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

	// �V���b�t��
	std::mt19937_64 get_rand_mt;
	std::shuffle(possible.begin(), possible.end(), get_rand_mt);

	// �A�C�e���i�[
	type = possible.begin()->type;
	key = possible.begin()->key;
	itemName = getItemName((int)possible.begin()->type + 1, possible.begin()->key);
	setUserItem((int)possible.begin()->type + 1, possible.begin()->key);
	Items[(int)possible.begin()->type].at(possible.begin()->key) = true;

	return true;
}

String User::getItemName(int game_id, int key){
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT Items.name FROM Items WHERE Items.game_id = ? AND Items.key = ?;";
	String name;

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, game_id);//1�ڂ́H��id�ɂ���
	sqlite3_bind_int(stmt, 2, key);//2�ڂ́H��game_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			std::string str((char*)sqlite3_column_text(stmt, 0));//0��ځi���O��UTF-8�Ŏ󂯎��UTF32�ɕϊ�����)
			name = Unicode::FromUTF8(str);
		}
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);

	return name;
}

void User::setUserItem(int game_id, int key) {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "UPDATE UserItems SET flag = 1 WHERE user_id = ? AND item_id = ?;";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, user_id);//1�ڂ́H��user_id�ɂ���
	sqlite3_bind_int(stmt, 2, getItemId(game_id, key));//2�ڂ́H��item_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return;
	}
	else {
		sqlite3_step(stmt);
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);

}

int User::getItemId(int game_id, int key) {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT Items.id FROM Items WHERE Items.game_id = ? AND Items.key = ?;";
	int item_id = 0;

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, game_id);//1�ڂ́H��id�ɂ���
	sqlite3_bind_int(stmt, 2, key);//2�ڂ́H��game_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			item_id = sqlite3_column_int(stmt, 0);
		}
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);

	return item_id;
}

//�|�C���g�̉��Z
bool User::addUserPoint(int addPoint) {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "UPDATE Users SET point = ? WHERE id = ?";

	user_point += addPoint;
	if (user_point >= 100000) {
		user_point = 99999;
	}
	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, user_point);//1�ڂ́H��point�ɂ���
	sqlite3_bind_int(stmt, 2, user_id);//2�ڂ́H��user_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return true;
}
//�|�C���g�̌��Z
bool User::subUserPoint(int subPoint) {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "UPDATE Users SET point = ? WHERE id = ?";

	user_point -= subPoint;
	if (user_point < 0) {
		user_point = 0;
	}
	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, user_point);//1�ڂ́H��point�ɂ���
	sqlite3_bind_int(stmt, 2, user_id);//2�ڂ́H��user_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return true;
}
int User::getUserPoint() {
	return user_point;
}


bool User::setTotalPlayTime() {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "UPDATE Users SET total_play_time = ? WHERE id = ?";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int64(stmt, 1, user_total_play_time + TotalPlayTimeTimer::getSecond());//1�ڂ́H��point�ɂ���
	sqlite3_bind_int(stmt, 2, user_id);//2�ڂ́H��user_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return true;
}

bool User::addGameScore(GAME_TYPE type, int score) {
	if (score < 0 || score > 100) { return false; }
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "INSERT INTO GameScores(user_id, game_id, score1, play_date) VALUES(?, ?, ?, date('now'));";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1�ڂ́H��user_id�ɂ���
	sqlite3_bind_int(stmt, 2, (int)type + 1);//2�ڂ́H��game_id�ɂ���
	sqlite3_bind_int(stmt, 3, score);//3�ڂ́H��score�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		sqlite3_step(stmt);
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return true;
}

int User::getGameHighScore(GAME_TYPE type) {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT MAX(score1) FROM GameScores WHERE user_id = ? AND game_id = ?;";
	int highScore = 0;

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1�ڂ́H��id�ɂ���
	sqlite3_bind_int(stmt, 2, (int)type + 1);//2�ڂ́H��game_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return 0;
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			highScore = sqlite3_column_int(stmt, 0);
		}
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);

	return highScore;
}


int User::getGamePlayCount(GAME_TYPE type) {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT COUNT(*) FROM GameScores WHERE user_id = ? AND game_id = ?;";
	int playCount = 0;

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1�ڂ́H��id�ɂ���
	sqlite3_bind_int(stmt, 2, (int)type + 1);//2�ڂ́H��game_id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return 0;
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			playCount = sqlite3_column_int(stmt, 0);
		}
	}

	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);

	return playCount;
}

float User::getItemAcquisitionRate() {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT COUNT(*) FROM UserItems WHERE user_id = ?;";
	int allRows = 0;

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1�ڂ́H��id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			allRows = sqlite3_column_int(stmt, 0);
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);


	//�ϐ�������
	err = 0;
	stmt = NULL;//�X�e�[�g�����g�n���h��
	pzTest = NULL;
	sql = "SELECT COUNT(*) FROM UserItems WHERE user_id = ? AND flag = 1;";
	int trueRows = 0;

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1�ڂ́H��id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			trueRows = sqlite3_column_int(stmt, 0);
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	if (allRows == 0) {
		return 0;
	}
	return (float)trueRows / allRows;
}

String User::getTotalPlayTime() {
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT total_play_time FROM Users WHERE id = ?;";

	int64 total_play_time = 0;

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, getUser_Id());//1�ڂ́H��id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
		return false;
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			total_play_time = sqlite3_column_int64(stmt, 0);
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);

	//���݂̃v���C���Ԃ𑫂�
	total_play_time += TotalPlayTimeTimer::getSecond();

	String playTimeStr = U"";
	if (total_play_time / 3600 > 0) {
		playTimeStr = playTimeStr + Format((int)total_play_time / 3600) + U"����";
		total_play_time %= 3600;
	}
	
	if (total_play_time / 60 > 0) {
		playTimeStr = playTimeStr + Format((int)total_play_time / 60) + U"��";
		total_play_time %= 60;
	}
	else {
		playTimeStr = playTimeStr + U"0��";
	}
	return playTimeStr;
}