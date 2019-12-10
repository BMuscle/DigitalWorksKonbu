#include "SelectSaveData.h"

#define FRAME_CENTER_X (Window::ClientWidth() / 2)		//�^�񒆂̃t���[���̈ʒuX
#define FRAME_CENTER_Y (Window::ClientHeight() / 2)		//�^�񒆂̃t���[���̈ʒuY
#define FRAME_INTERVAL (Window::ClientHeight() * 0.2)	//�t���[���̊Ԋu

#define SELECT_INTERVAL_COUNT (60 * 0.2)

SelectSaveData::SelectSaveData(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"selectSDfont", 70);
	FontAsset::Preload(U"selectSDfont");
	TextureAsset::Register(U"selectSDback", U"resources/images/backs/selectsavedata.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectSDframe", U"resources/images/items/selectsavedata/frame.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectSDframeon", U"resources/images/items/selectsavedata/frameon.png", AssetParameter::LoadAsync());

	MySqlite3::getDB();//������g�p����SQL�������s���ăf�[�^�̎擾���K�v�ɂȂ�B

	for (int i = 0; i < USER_SIZE; i++) {	//�Z�[�u�f�[�^�t���[���̏�����
		user_frame[i].id = i + 1;			//�f�[�^�x�[�X��ID�͂P�n�܂�Ȃ̂łP����w��
		//if���ł������[�U�[�����󔒂Ȃ�No Data���i�[����
		user_frame[i].user_name = U"No Data";		//���O�̎w��
		user_frame[i].x = FRAME_CENTER_X;	//X���W���w��
		user_frame[i].y = (int)(FRAME_CENTER_Y + (FRAME_INTERVAL * (i - (USER_SIZE / 2))));//Y���W�𒆐S����㉺�ɂȂ�悤�Ɏw��
	}

	//�ϐ��̏�����
	selectedUser = 0;//�����I������Ă��郆�[�U�[����ԏ�̂��̂�
	selectCountPrev = 0;
}
SelectSaveData::~SelectSaveData(void) {
	FontAsset::Unregister(U"selectSDfont");
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

		/*if(){//�Z�[�u�f�[�^����������I�����悤�Ƃ��Ă���Ȃ�΁A
			//id�̃`�F�b�N�������B�iid��l�߂ɂȂ�悤�Ƀ`�F�b�N�j
			MySceneManager::setNextScene(SCENE::CREATE_SAVEDATA);
		}
		*/
		MySceneManager::setNextScene(SCENE::CREATE_SAVEDATA);
		//MySceneManager::setNextScene(SCENE::SELECT_MODE);
	}
	updateFrameCount();
	if (!(MyKey::getUpKey() == true && MyKey::getDownKey() == true)) {
		if (MyKey::getUpKey()) {
			rotateSelectedUser(true);
		}
		if (MyKey::getDownKey()) {
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