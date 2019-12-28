#include "CreateSaveData.h"

//�e�L�X�g�{�b�N�X�̍��W �� ��`
#define NAMEBOX_X (Window::ClientWidth() * 0.6)
#define NAMEBOX_Y (Window::ClientHeight() * 0.8)
#define NAMEBOX_W (Window::ClientWidth() * 0.3)
//�A�C�e���̈ʒu�̊Ԋu���`
#define ITEM_INTERVAL (Window::ClientHeight() * 0.2)
//�|�b�v�A�b�v�̃{�^���̗���Ă���Ԋu���`
#define POPUP_INTERVAL (Window::ClientWidth() * 0.07)

CreateSaveData::CreateSaveData(void) {
	isStart = false;
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"createSDfont", 70);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());

	//�|�b�v�A�b�v���[�h
	TextureAsset::Register(U"createSDpopup", U"resources/images/items/createsavedata/popup.png", AssetParameter::LoadAsync());	//����A�߂�{�^���̏�����

	//�߂�{�^������{�^��������
	button[(int)BUTTON::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/button", U"�߂�", 50, 100, 800, false);
	button[(int)BUTTON::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/button", U"����", 50, 1800, 800, false);
	
	//�|�b�v�A�b�v�̃{�^��������
	popUpButton[(int)POPUP::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/popup", U"�{���ɗǂ��H", 50, (int)(Window::ClientWidth() / 2) + (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, true);
	popUpButton[(int)POPUP::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/popup", U"����ς�߂�", 40, (int)(Window::ClientWidth() / 2) - (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, false);

	//�ϐ��̏�����
	nameFont = Font(50);//�e�L�X�g�{�b�N�X�̃t�H���g
	namebox = TextBox(nameFont, Vec2(100, 100), NAMEBOX_W, 15, U"");
	namebox.setCenter(Vec2(NAMEBOX_X, NAMEBOX_Y));
	namebox.setActive(false);//������ԂŃe�L�X�g�{�b�N�X���A�N�e�B�u��
	selectState = SELECT_STATE::TEXT;//������Ԃ̑I����Ԃ̓e�L�X�g�{�b�N�X��
	popUpState = POPUP::NONE;//�|�b�v�A�b�v�I���̏�����Ԃ�YES��
}
CreateSaveData::~CreateSaveData(void) {
	FontAsset::Unregister(U"createSDfont");
	TextureAsset::Unregister(U"createSDback");
	delete button[(int)BUTTON::DECISION];
	delete button[(int)BUTTON::RETURN];


	int id = User::getSaveDataSize() + 1;//���݂̃Z�[�u�f�[�^���̂P��ɐV�K�Z�[�u�f�[�^���쐬����
	if (id > 0) {
		User::createSaveData(id, namebox.getText());//�Z�[�u�f�[�^�쐬
		User::saveDataAccess(id);
	}
	else {
		//�G���[
	}
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")&&
		TextureAsset::IsReady(U"createSDpopup")&&
		popUpButton[(int)BUTTON::DECISION]->isReady()&&
		popUpButton[(int)BUTTON::RETURN]->isReady() &&
		button[(int)BUTTON::DECISION]->isReady()&&
		button[(int)BUTTON::RETURN]->isReady()) {
		return true;
	}
	return false;
}
void CreateSaveData::start(void) {
	isStart = true;
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->play();
	namebox.setActive(true);//���[�h�I����Ńe�L�X�g�{�b�N�X���A�N�e�B�u��
}
void CreateSaveData::update(void) {//�v�Z����
	if (namebox.isActive()) {//�e�L�X�g�{�b�N�X���A�N�e�B�u�̎�
		namebox.update();
	}
	
	selectUpdate();//���݂̑I����ԂɑΉ�����v�Z����
	selectMove();//�ړ�����

	//���̓`�F�b�N������(�Z���N�g����Ă�����̂��߂�{�^���̏ꍇ��O�j
	if (namebox.getText().isEmpty() && selectState != SELECT_STATE::DECISION) {//�����񂪋�Ȃ�I������
		namebox.setActive(true);
		selectState = SELECT_STATE::TEXT;
		button[(int)BUTTON::DECISION]->setSelect(false);
		button[(int)BUTTON::RETURN]->setSelect(false);
	}
}


void CreateSaveData::draw(void) {//�`�揈��
	//�w�i�`��
	TextureAsset(U"createSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

	//�{�^���̕`��
	button[(int)BUTTON::DECISION]->draw();
	button[(int)BUTTON::RETURN]->draw();
	//�e�L�X�g�{�b�N�X�̕`��
	namebox.draw();
	namebox.drawOverlay();
	FontAsset(U"createSDfont")(U"�{�l����").drawAt(NAMEBOX_X - FontAsset(U"createSDfont").fontSize() * 3 - NAMEBOX_W / 2, NAMEBOX_Y, ColorF(0, 0, 0));
	if (selectState == SELECT_STATE::POPUP) {//�e�L�X�g�{�b�N�X����A�N�e�B�u�̎��|�b�v�A�b�v��\������
		popUpDraw();
	}
}


void CreateSaveData::selectUpdate() {//���݂̈ړ���ԂɑΉ�����v�Z����
	switch (selectState)//���݂̑I�����
	{
	case CreateSaveData::SELECT_STATE::RETURN:
		if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
			selectState = SELECT_STATE::POPUP;								//���݂̑I����Ԃ��|�b�v�A�b�v��
			popUpState = POPUP::RETURN;										//�|�b�v�A�b�v�\��
		}
		return;
	case CreateSaveData::SELECT_STATE::TEXT:
		if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
			selectState = SELECT_STATE::RETURN;								//�e�L�X�g�{�b�N�X�ŃG���^�[�������Ƃ�YES��I��������
			button[(int)BUTTON::DECISION]->setSelect(true);
			namebox.setActive(false);
		}
		return;
	case CreateSaveData::SELECT_STATE::DECISION:
		if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
			MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);			//�Z�[�u�f�[�^�I����ʂ֖߂�
		}
		return;
	case CreateSaveData::SELECT_STATE::POPUP://���݃|�b�v�A�b�v�\����
		if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
			switch (popUpState)
			{
			case CreateSaveData::POPUP::RETURN://���[�h�I���ֈړ�
				MySceneManager::setNextScene(SCENE::SELECT_MODE);			//���[�h�I���փV�[���ڍs�v��
				TotalPlayTimeTimer::start();								//�v���C���Ԍv���J�n
				break;
			case CreateSaveData::POPUP::DECISION://�e�L�X�g�I����Ԃ֖߂�
				selectState = SELECT_STATE::TEXT;							//���݂̑I����Ԃ��e�L�X�g�{�b�N�X��
				namebox.setActive(true);									//�e�L�X�g�{�b�N�X���A�N�e�B�u��
				button[(int)BUTTON::DECISION]->setSelect(false);			//�{�^���𗼕��Ƃ���A�N�e�B�u��
				button[(int)BUTTON::RETURN]->setSelect(false);
				break;
			}
		}
		else {//���E�ړ�
			if (MyKey::getLeftKeyDown()) {
				popUpState = POPUP::DECISION;
			}
			if (MyKey::getRightKeyDown()) {
				popUpState = POPUP::RETURN;
			}
		}
		return;
	}
}
void CreateSaveData::selectMove() {//�I����Ԃ̑J��
	if (MyKey::getRightKeyDown()) {//�E�L�[����
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::TEXT://�e�L�X�g������{�^��
			namebox.setActive(false);
			selectState = SELECT_STATE::RETURN;
			button[(int)BUTTON::DECISION]->setSelect(true);
			break;
		case CreateSaveData::SELECT_STATE::DECISION://�߂�{�^�����e�L�X�g
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			button[(int)BUTTON::RETURN]->setSelect(false);
			break;
		}
	}
	if (MyKey::getLeftKeyDown()) {//���L�[����
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::RETURN://����{�^�����e�L�X�g
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			button[(int)BUTTON::DECISION]->setSelect(false);
			break;
		case CreateSaveData::SELECT_STATE::TEXT://�e�L�X�g���߂�{�^��
			namebox.setActive(false);
			selectState = SELECT_STATE::DECISION;
			button[(int)BUTTON::RETURN]->setSelect(true);
			break;
		}
	}
}

void CreateSaveData::popUpDraw() {//�|�b�v�A�b�v�̕`��
	//�|�b�v�A�b�v�w�i��`��
	TextureAsset(U"createSDpopup").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	switch (popUpState)
	{
	case CreateSaveData::POPUP::RETURN://YES���I������Ă���Ƃ� �I����Ԃ�ύX
		popUpButton[(int)POPUP::RETURN]->setSelect(true);
		popUpButton[(int)POPUP::DECISION]->setSelect(false);
		break;
	case CreateSaveData::POPUP::DECISION://NO���I������Ă���Ƃ� �I����Ԃ�ύX
		popUpButton[(int)POPUP::RETURN]->setSelect(false);
		popUpButton[(int)POPUP::DECISION]->setSelect(true);
		break;
	}
	//�`�揈��
	popUpButton[(int)POPUP::RETURN]->draw();
	popUpButton[(int)POPUP::DECISION]->draw();
}