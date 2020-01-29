#include "SelectSaveData.h"

#define FRAME_CENTER_X (Scene::Width() / 2)		//�^�񒆂̃t���[���̈ʒuX
#define FRAME_CENTER_Y (Scene::Height() / 2 + 150)		//�^�񒆂̃t���[���̈ʒuY
#define FRAME_INTERVAL (Scene::Height() * 0.23)	//�t���[���̊Ԋu

//�|�b�v�A�b�v�̃{�^���̗���Ă���Ԋu���`
#define POPUP_INTERVAL (Scene::Width() * 0.07)

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

	TextureAsset::Register(U"selectSDdeleteon", U"resources/images/items/selectsavedata/delete/on.png");
	TextureAsset::Register(U"selectSDdeleteoff", U"resources/images/items/selectsavedata/delete/off.png");
	TextureAsset::Register(U"selectSDpopup", U"resources/images/items/selectsavedata/popup.png");
	//���ʉ����[�h


	//�Z�[�u�f�[�^�擾��
	MySqlite3::getDB();//������g�p����SQL�������s���ăf�[�^�̎擾���K�v�ɂȂ�B

	for (int i = 0; i < USER_SIZE; i++) {	//�Z�[�u�f�[�^�t���[���̏�����
		user_frame[i].id = i + 1;			//�f�[�^�x�[�X��ID�͂P�n�܂�Ȃ̂łP����w��
		if (User::isUser(i + 1)) {//���[�U�[�����݂���Ȃ烆�[�U�f�[�^�i�[
			int64 totalplaytime = 0;
			User::simpleSaveDataAccess(i + 1, user_frame[i].user_name, totalplaytime);
			if ((int)(totalplaytime / 3600) > 0) {//�v���C���Ԃ��P���Ԃ𒴂��Ă���ꍇ
				user_frame[i].total_play_time = U"�v���C����" + Format(totalplaytime / 3600) + U" ����";
			}
			else {//�P���Ԓ����Ă��Ȃ��̂ŕ���
				user_frame[i].total_play_time = U"�v���C����" + Format(totalplaytime / 60) + U" ��";
			}
		}
		else {
			user_frame[i].user_name = U"No Data";		//���O�̎w��
			user_frame[i].total_play_time = U"";//�v���C���Ԃ̏�����
		}
		user_frame[i].x = FRAME_CENTER_X;	//X���W���w��
		user_frame[i].y = (int)(FRAME_CENTER_Y + (FRAME_INTERVAL * (i - (USER_SIZE / 2))));//Y���W�𒆐S����㉺�ɂȂ�悤�Ɏw��
	}

	//�|�b�v�A�b�v�̃{�^��������
	popUpButton[(int)POPUP::DECISION] = new MyImageButton(U"resources/images/items/selectsavedata/popupdeci", U"", 0, (int)(Scene::Width() / 2) + (int)POPUP_INTERVAL, (int)Scene::Height() * 0.70, true);
	popUpButton[(int)POPUP::RETURN] = new MyImageButton(U"resources/images/items/selectsavedata/popupretu", U"", 0, (int)(Scene::Width() / 2) - (int)POPUP_INTERVAL, (int)Scene::Height() * 0.70, false);


	//�ϐ��̏�����
	selectedUser = 0;//�����I������Ă��郆�[�U�[����ԏ�̂��̂�
	selectCountPrev = 0;
	selectDeleteButton = false;
	popUpState = POPUP::NONE;
	isPopUp = false;
}
SelectSaveData::~SelectSaveData(void) {
	delete backAudio;
	FontAsset::Unregister(U"selectSDfont");
	FontAsset::Unregister(U"selectSDfontsmall");
	TextureAsset::Unregister(U"selectSDback");
	TextureAsset::Unregister(U"selectSDframe");
	TextureAsset::Unregister(U"selectSDframeon");
	TextureAsset::Unregister(U"selectSDdeleteon");
	TextureAsset::Unregister(U"selectSDdeleteoff");
	TextureAsset::Unregister(U"selectSDpopup");
	AudioAsset::Unregister(U"selectSDdecision");
	AudioAsset::Unregister(U"selectSDcursor");

	delete popUpButton[(int)POPUP::DECISION];
	delete popUpButton[(int)POPUP::RETURN];
}
bool SelectSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"selectSDback")&&
		TextureAsset::IsReady(U"selectSDframe")&&
		TextureAsset::IsReady(U"selectSDframeon")&&
		popUpButton[(int)POPUP::DECISION]->isReady() &&
		popUpButton[(int)POPUP::RETURN]->isReady()) {
		return true;
	}
	return false;
}
void SelectSaveData::start(void) {
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->setVolume(0.1);
	backAudio->play();
}
void SelectSaveData::update(void) {

	if (isPopUp) {//�|�b�v�A�b�v�I����Ԃ̏ꍇ
		if (MyKey::getDecisionKey()) {
			if (popUpState == POPUP::DECISION) {
				deleteSaveData();
				GeneralSoundEffects::play(SE_NAME::DECISION);
			}
			else if (popUpState == POPUP::RETURN) {
				GeneralSoundEffects::play(SE_NAME::BACK);

			}
			isPopUp = false;
			selectDeleteButton = false;
			popUpState = POPUP::NONE;
		}
		else if (MyKey::getRightKeyDown()) {
			popUpState = POPUP::DECISION;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		else if (MyKey::getLeftKeyDown()) {
			popUpState = POPUP::RETURN;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		return;
	}

	//�폜�{�^���I����Ԃ̏ꍇ
	if (selectDeleteButton && MyKey::getDecisionKey()) {
		isPopUp = true;
		popUpState = POPUP::DECISION;
		GeneralSoundEffects::play(SE_NAME::DECISION);
		return;
	}

	if (MyKey::getDecisionKey()) {//�I������Ă���Z�[�u�f�[�^�ɂ�蕪��A�V�[���ڍs����
		if (User::isUser(getSelectUser_Id())) {//���[�U�[�����݂��Ă���ꍇ
			MySceneManager::setNextScene(SCENE::SELECT_MODE);	//���[�h�I���ֈڍs
			User::saveDataAccess(getSelectUser_Id());				//�Z�[�u�f�[�^�փA�N�Z�X���f�[�^��ێ�
			TotalPlayTimeTimer::start();						//�v���C���ԃJ�E���g�J�n
		}
		else {
			MySceneManager::setNextScene(SCENE::CREATE_SAVEDATA);
		}
		
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}else if (MyKey::getReturnKey()) {
		MySceneManager::setNextScene(SCENE::TITLE);
	}
	else if (MyKey::getRightKeyDown()) {//���[�U�[���݂���Ȃ�폜�{�^����I��������
		if (!selectDeleteButton && User::isUser(getSelectUser_Id())) {
			selectDeleteButton = true;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
	}
	else if (MyKey::getLeftKeyDown() && selectDeleteButton) {
		selectDeleteButton = false;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}




	updateFrameCount();//�t���[�������J�E���g�A�b�v����
	if (!(MyKey::getUpKeyPressed() == true && MyKey::getDownKeyPressed() == true)) {
		if (MyKey::getUpKeyPressed()) {//�Z�[�u�f�[�^�I����Ԃ�������ɉ�]
			rotateSelectedUser(true);
			if (!User::isUser(getSelectUser_Id())) {
				selectDeleteButton = false;
			}
		}
		if (MyKey::getDownKeyPressed()) {//�Z�[�u�f�[�^�I����Ԃ��������ɉ�]
			rotateSelectedUser(false);
			if (!User::isUser(getSelectUser_Id())) {
				selectDeleteButton = false;
			}
		}
	}


}
void SelectSaveData::draw(void) {
	//�w�i�`��
	TextureAsset(U"selectSDback").drawAt(Scene::Width() / 2, Scene::Height() / 2);


	//�Z�[�u�f�[�^�̃t���[���摜�`��
	for (int i = 0; i < USER_SIZE; i++) {
		TextureAsset(U"selectSDframe").drawAt(user_frame[i].x, user_frame[i].y);
		//�폜�{�^���`��
		if (User::isUser(i + 1)) {
			if (selectDeleteButton && i == selectedUser) {
				TextureAsset(U"selectSDdeleteon").drawAt(user_frame[i].x + 570, user_frame[i].y - 10);
			}
			else {
				TextureAsset(U"selectSDdeleteoff").drawAt(user_frame[i].x + 570, user_frame[i].y - 10);
			}
		}
	}
	//�I������Ă�����̂��������ĕ`��
	TextureAsset(U"selectSDframeon").drawAt(user_frame[selectedUser].x, user_frame[selectedUser].y);

	//�Z�[�u�f�[�^�̏���`�悷��
	for (int i = 0; i < USER_SIZE; i++) {
		FontAsset(U"selectSDfont")(user_frame[i].user_name).drawAt(user_frame[i].x, user_frame[i].y - 20 , (ColorF(0,0,0)));
		FontAsset(U"selectSDfontsmall")(user_frame[i].total_play_time).drawAt(user_frame[i].x, user_frame[i].y + 40, (ColorF(0, 0, 0)));
	}

	if (isPopUp) {
		//�|�b�v�A�b�v�w�i��`��
		TextureAsset(U"selectSDpopup").drawAt(Scene::Width() * 0.5 - 35, Scene::Height() * 0.6);
		switch (popUpState)
		{
		case POPUP::DECISION://YES���I������Ă���Ƃ� �I����Ԃ�ύX
			//�`�揈��
			popUpButton[(int)POPUP::DECISION]->drawNotWord(true);
			popUpButton[(int)POPUP::RETURN]->drawNotWord(false);
			break;
		case POPUP::RETURN://NO���I������Ă���Ƃ� �I����Ԃ�ύX
			//�`�揈��
			popUpButton[(int)POPUP::DECISION]->drawNotWord(false);
			popUpButton[(int)POPUP::RETURN]->drawNotWord(true);
			break;
		}

	}
}


//�t���[�������J�E���g�A�b�v����
void SelectSaveData::updateFrameCount() {
	frameCount++;
	if (frameCount > 60 * 3000) {//����l�`�F�b�N
		frameCount = 0;
	}
}

//���[�U�[�̑I����Ԃ��X�V����(true = ����� false = ������)
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
		//���ʉ���炷
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
}

int SelectSaveData::getSelectUser_Id() {
	return selectedUser + 1;
}

void SelectSaveData::deleteSaveData() {
	User::deleteUserData(getSelectUser_Id());
	//�f�[�^�i�[������
	for (int i = 0; i < USER_SIZE; i++) {	//�Z�[�u�f�[�^�t���[���̏�����
		user_frame[i].id = i + 1;			//�f�[�^�x�[�X��ID�͂P�n�܂�Ȃ̂łP����w��
		if (User::isUser(i + 1)) {//���[�U�[�����݂���Ȃ烆�[�U�f�[�^�i�[
			int64 totalplaytime = 0;
			User::simpleSaveDataAccess(i + 1, user_frame[i].user_name, totalplaytime);
			if ((int)(totalplaytime / 3600) > 0) {//�v���C���Ԃ��P���Ԃ𒴂��Ă���ꍇ
				user_frame[i].total_play_time = U"�v���C����" + Format(totalplaytime / 3600) + U" ����";
			}
			else {//�P���Ԓ����Ă��Ȃ��̂ŕ���
				user_frame[i].total_play_time = U"�v���C����" + Format(totalplaytime / 60) + U" ��";
			}
		}
		else {
			user_frame[i].user_name = U"No Data";		//���O�̎w��
			user_frame[i].total_play_time = U"";//�v���C���Ԃ̏�����
		}
		user_frame[i].x = FRAME_CENTER_X;	//X���W���w��
		user_frame[i].y = (int)(FRAME_CENTER_Y + (FRAME_INTERVAL * (i - (USER_SIZE / 2))));//Y���W�𒆐S����㉺�ɂȂ�悤�Ɏw��
	}
}