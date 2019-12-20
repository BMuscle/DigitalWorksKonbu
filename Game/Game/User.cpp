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
	return Items[((int)type) + 1][key];
}