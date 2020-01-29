#include "CreateSaveData.h"

//�e�L�X�g�{�b�N�X�̍��W �� ��`
#define NAMEBOX_X (Scene::Width() * 0.5)
#define NAMEBOX_Y (Scene::Height() * 0.55)
#define NAMEBOX_W (Scene::Width() * 0.18)
//�A�C�e���̈ʒu�̊Ԋu���`
#define ITEM_INTERVAL (Scene::Height() * 0.2)
//�|�b�v�A�b�v�̃{�^���̗���Ă���Ԋu���`
#define POPUP_INTERVAL (Scene::Width() * 0.07)

//�{�^���̉�ʒ[���痣��Ă��鋗��
#define BUTTON_OFFSET_X (600)

#define BUTTON_RETURN_X (BUTTON_OFFSET_X)
#define BUTTON_DECISION_X (Scene::Width() - BUTTON_OFFSET_X)

#define BUTTON_Y NAMEBOX_Y

CreateSaveData::CreateSaveData(int user_id) {
	isStart = false;
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"createSDfont", 40);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());

	//�|�b�v�A�b�v���[�h
	TextureAsset::Register(U"createSDpopup", U"resources/images/items/createsavedata/popup.png", AssetParameter::LoadAsync());	//����A�߂�{�^���̏�����

	//�߂�{�^������{�^��������
	button[(int)BUTTON::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/return", U"", 0, BUTTON_RETURN_X, BUTTON_Y, false);
	button[(int)BUTTON::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/decision", U"", 0, BUTTON_DECISION_X, BUTTON_Y, false);
	
	//�|�b�v�A�b�v�̃{�^��������
	popUpButton[(int)POPUP::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/popupdeci", U"", 0, (int)(Scene::Width() / 2) + (int)POPUP_INTERVAL, (int)Scene::Height() * 0.6, true);
	popUpButton[(int)POPUP::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/popupretu", U"", 0, (int)(Scene::Width() / 2) - (int)POPUP_INTERVAL, (int)Scene::Height() * 0.6, false);

	//�ϐ��̏�����
	createUser_Id = user_id;//���[�U�[ID

	nameFont = Font(40);//�e�L�X�g�{�b�N�X�̃t�H���g
	namebox = TextBox(nameFont, Vec2(100, 100), NAMEBOX_W, 8, U"");
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

	delete popUpButton[(int)POPUP::DECISION];
	delete popUpButton[(int)POPUP::RETURN];

	delete backAudio;
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")&&
		TextureAsset::IsReady(U"createSDpopup")&&
		popUpButton[(int)POPUP::DECISION]->isReady() &&
		popUpButton[(int)POPUP::RETURN]->isReady() &&
		button[(int)BUTTON::DECISION]->isReady()&&
		button[(int)BUTTON::RETURN]->isReady()) {
		return true;
	}
	return false;
}
void CreateSaveData::start(void) {
	isStart = true;
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/createSD.wav");
	backAudio->setLoop(true);
	backAudio->setVolume(0.1);
	backAudio->play();
	namebox.setActive(true);//���[�h�I����Ńe�L�X�g�{�b�N�X���A�N�e�B�u��
}
void CreateSaveData::update(void) {//�v�Z����
	namebox.update();
	selectUpdate();//���݂̑I����ԂɑΉ�����v�Z����
	selectMove();//�ړ�����

	//���̓`�F�b�N������(�Z���N�g����Ă�����̂��߂�{�^���̏ꍇ��O�j
	if (namebox.getText().isEmpty() &&
		selectState != SELECT_STATE::RETURN &&
		!namebox.isActive()) {//�����񂪋�Ȃ�I������
		namebox.setActive(true);
		selectState = SELECT_STATE::TEXT;
	}
	if (selectState != SELECT_STATE::TEXT) {
		namebox.setActive(false);
	}
	
}


void CreateSaveData::draw(void) {//�`�揈��
	//�w�i�`��
	TextureAsset(U"createSDback").drawAt(Scene::Width() / 2, Scene::Height() / 2);

	//�{�^���̕`��
	button[(int)BUTTON::DECISION]->drawNotWord(selectState == SELECT_STATE::DECISION);
	button[(int)BUTTON::RETURN]->drawNotWord(selectState == SELECT_STATE::RETURN);

	//�e�L�X�g�{�b�N�X�̕`��
	namebox.draw();
	namebox.drawOverlay();
	//FontAsset(U"createSDfont")(U"�{�l����").drawAt(NAMEBOX_X - FontAsset(U"createSDfont").fontSize() * 3 - NAMEBOX_W / 2, NAMEBOX_Y, ColorF(0, 0, 0));
	FontAsset(U"createSDfont")(U"�{�l����").drawAt(NAMEBOX_X, NAMEBOX_Y - 70, ColorF(0, 0, 0));

	//�e�L�X�g�{�b�N�X����A�N�e�B�u�̎��|�b�v�A�b�v��\������
	if (selectState == SELECT_STATE::POPUP) {
		popUpDraw();
	}
}


void CreateSaveData::selectUpdate() {//���݂̈ړ���ԂɑΉ�����v�Z����
	switch (selectState)//���݂̑I�����
	{
	case CreateSaveData::SELECT_STATE::DECISION:
		if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
			selectState = SELECT_STATE::POPUP;								//���݂̑I����Ԃ��|�b�v�A�b�v��
			popUpState = POPUP::DECISION;										//�|�b�v�A�b�v�\��
			GeneralSoundEffects::play(SE_NAME::DECISION);
		}
		return;
	case CreateSaveData::SELECT_STATE::TEXT:
		if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
			selectState = SELECT_STATE::DECISION;								//�e�L�X�g�{�b�N�X�ŃG���^�[�������Ƃ�YES��I��������
			namebox.setActive(false);
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		return;
	case CreateSaveData::SELECT_STATE::RETURN:
		if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
			MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);			//�Z�[�u�f�[�^�I����ʂ֖߂�
		}
		return;
	case CreateSaveData::SELECT_STATE::POPUP://���݃|�b�v�A�b�v�\����
		popUpUpdate();
		return;
	}
}
void CreateSaveData::selectMove() {//�I����Ԃ̑J��
	if (MyKey::getRightKeyDown()) {//�E�L�[����
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::TEXT://�e�L�X�g������{�^��
			namebox.setActive(false);
			selectState = SELECT_STATE::DECISION;
			break;
		case CreateSaveData::SELECT_STATE::RETURN://�߂�{�^�����e�L�X�g
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			break;
		}
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
	if (MyKey::getLeftKeyDown()) {//���L�[����
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::DECISION://����{�^�����e�L�X�g
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			break;
		case CreateSaveData::SELECT_STATE::TEXT://�e�L�X�g���߂�{�^��
			namebox.setActive(false);
			selectState = SELECT_STATE::RETURN;
			break;
		}
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
}

void CreateSaveData::popUpUpdate() {//�|�b�v�A�b�v�̌v�Z����
	if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
		switch (popUpState)
		{
		case CreateSaveData::POPUP::DECISION://���[�h�I���ֈړ�
			MySceneManager::setNextScene(SCENE::SELECT_MODE);			//���[�h�I���փV�[���ڍs�v��
			createData();												//�Z�[�u�f�[�^�쐬
			TotalPlayTimeTimer::start();								//�v���C���Ԍv���J�n
			GeneralSoundEffects::play(SE_NAME::DECISION);				//���艹
			break;
		case CreateSaveData::POPUP::RETURN://�e�L�X�g�I����Ԃ֖߂�
			selectState = SELECT_STATE::TEXT;							//���݂̑I����Ԃ��e�L�X�g�{�b�N�X��
			namebox.setActive(true);
			GeneralSoundEffects::play(SE_NAME::BACK);//�e�L�X�g�{�b�N�X���A�N�e�B�u��
			break;
		}
	}

	popUpMove();//�|�b�v�A�b�v�ړ�����
}

void CreateSaveData::popUpMove() {//�|�b�v�A�b�v�̈ړ��`�F�b�N�ړ�����
	if (MyKey::getLeftKeyDown()) {
		popUpState = POPUP::RETURN;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
	if (MyKey::getRightKeyDown()) {
		popUpState = POPUP::DECISION;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
}

void CreateSaveData::popUpDraw() {//�|�b�v�A�b�v�̕`��
	//�|�b�v�A�b�v�w�i��`��
	TextureAsset(U"createSDpopup").drawAt(Scene::Width() * 0.5, Scene::Height() * 0.45);
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

void CreateSaveData::createData() {//�Z�[�u�f�[�^�����ۂɍ쐬
	User::createSaveData(createUser_Id, namebox.getText());//�Z�[�u�f�[�^�쐬
	User::saveDataAccess(createUser_Id);
}
