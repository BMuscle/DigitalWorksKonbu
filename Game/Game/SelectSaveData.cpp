#include "SelectSaveData.h"

#define FRAME_CENTER_X (Window::ClientWidth() / 2)		//�^�񒆂̃t���[���̈ʒuX
#define FRAME_CENTER_Y (Window::ClientHeight() / 2)		//�^�񒆂̃t���[���̈ʒuY
#define FRAME_INTERVAL (Window::ClientHeight() * 0.2)	//�t���[���̊Ԋu

#define SELECT_INTERVAL_COUNT (60 * 0.2)

SelectSaveData::SelectSaveData(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"selectSDfont", 70);
	FontAsset::Preload(U"selectSDfont");
	FontAsset::Register(U"selectSDfontsmall", 40);
	FontAsset::Preload(U"selectSDfontsmall");
	TextureAsset::Register(U"selectSDback", U"resources/images/backs/selectsavedata.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectSDframe", U"resources/images/items/selectsavedata/frame.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectSDframeon", U"resources/images/items/selectsavedata/frameon.png", AssetParameter::LoadAsync());

	MySqlite3::getDB();//������g�p����SQL�������s���ăf�[�^�̎擾���K�v�ɂȂ�B

	for (int i = 0; i < USER_SIZE; i++) {	//�Z�[�u�f�[�^�t���[���̏�����
		user_frame[i].id = i + 1;			//�f�[�^�x�[�X��ID�͂P�n�܂�Ȃ̂łP����w��
		//if���ł������[�U�[�����󔒂Ȃ�No Data���i�[����
		user_frame[i].user_name = U"No Data";		//���O�̎w��
		user_frame[i].total_play_time = U"";//�v���C���Ԃ̏�����
		user_frame[i].x = FRAME_CENTER_X;	//X���W���w��
		user_frame[i].y = (int)(FRAME_CENTER_Y + (FRAME_INTERVAL * (i - (USER_SIZE / 2))));//Y���W�𒆐S����㉺�ɂȂ�悤�Ɏw��
	}

	//�ϐ��̏�����
	selectedUser = 0;//�����I������Ă��郆�[�U�[����ԏ�̂��̂�
	selectCountPrev = 0;
	currentUserSize = User::getSaveDataSize();//���݂̃��[�U�[�����i�[
	for (int i = 0; i < currentUserSize; i++) {//���[�U�[�����݂�����̂��X�V����
		int64 totalplaytime = 0;
		User::simpleSaveDataAccess(i+1, user_frame[i].user_name, totalplaytime);
		if ((int)(totalplaytime / 3600) >= 0) {//�v���C���Ԃ��P���Ԃ𒴂��Ă���ꍇ
			user_frame[i].total_play_time = U"�v���C����" + Format(totalplaytime / 3600) + U" ����";
		}
		else {//�P���Ԓ����Ă��Ȃ��̂ŕ���
			user_frame[i].total_play_time = U"�v���C����" + Format(totalplaytime / 60) + U" ��";
		}
	}
}
SelectSaveData::~SelectSaveData(void) {
	delete backAudio;
	FontAsset::Unregister(U"selectSDfont");
	FontAsset::Unregister(U"selectSDfontsmall");
	TextureAsset::Unregister(U"selectSDback");
	TextureAsset::Unregister(U"selectSDframe");
	TextureAsset::Unregister(U"selectSDframeon");
}
bool SelectSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"selectSDback")&&
		TextureAsset::IsReady(U"selectSDframe")&&
		TextureAsset::IsReady(U"selectSDframeon")) {
		return true;
	}
	return false;
}
void SelectSaveData::start(void) {
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void SelectSaveData::update(void) {
	if (MyKey::getDecisionKey()) {

		if (selectedUser < currentUserSize){//���[�U�[����菬�����ꏊ�i���Ƀ��[�U�[�����݂���Ƃ����I�����Ă���ꍇ)
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			User::saveDataAccess(selectedUser + 1);
		}
		else {
			MySceneManager::setNextScene(SCENE::CREATE_SAVEDATA);
		}
	}
	updateFrameCount();
	if (!(MyKey::getUpKeyPressed() == true && MyKey::getDownKeyPressed() == true)) {
		if (MyKey::getUpKeyPressed()) {
			rotateSelectedUser(true);
		}
		if (MyKey::getDownKeyPressed()) {
			rotateSelectedUser(false);
		}
	}


}
void SelectSaveData::draw(void) {
	//�w�i�`��
	TextureAsset(U"selectSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

	//�Z�[�u�f�[�^�I��
	FontAsset(U"selectSDfont")(U"�`�Z�[�u�f�[�^�̑I���`").drawAt(Window::ClientWidth() / 2, user_frame[0].y - FRAME_INTERVAL, ColorF(0, 0, 0));

	//�Z�[�u�f�[�^�̃t���[���摜�`��
	for (int i = 0; i < USER_SIZE; i++) {
		TextureAsset(U"selectSDframe").drawAt(user_frame[i].x, user_frame[i].y);
	}
	//�I������Ă�����̂��������ĕ`��
	TextureAsset(U"selectSDframeon").drawAt(user_frame[selectedUser].x, user_frame[selectedUser].y);

	//�Z�[�u�f�[�^�̏���`�悷��
	for (int i = 0; i < USER_SIZE; i++) {
		FontAsset(U"selectSDfont")(user_frame[i].user_name).drawAt(user_frame[i].x, user_frame[i].y - 20 , (ColorF(0,0,0)));
		FontAsset(U"selectSDfontsmall")(user_frame[i].total_play_time).drawAt(user_frame[i].x, user_frame[i].y + 40, (ColorF(0, 0, 0)));
	}

	
}


void SelectSaveData::updateFrameCount() {
	frameCount++;
	if (frameCount > 60 * 3000) {//����l�`�F�b�N
		frameCount = 0;
	}
}

void SelectSaveData::rotateSelectedUser(bool isUp) {
	if (frameCount - selectCountPrev >= SELECT_INTERVAL_COUNT) {
		selectCountPrev = frameCount;
		if (isUp) {
			selectedUser--;
			if (selectedUser < 0) {
				selectedUser = USER_SIZE - 1;
			}
		}
		else {
			selectedUser++;
			if (selectedUser >= USER_SIZE) {
				selectedUser = 0;
			}
		}
	}
}