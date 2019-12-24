#include "Gacha.h"

constexpr int GACHA_PRICE = 500;

Gacha::Gacha(void) {
	//���[�h�G�t�F�N�g�̏�����
	simpleLoadEffect = new SimpleLoadEffect();

	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"gachafont", 70, AssetParameter::LoadAsync());
	FontAsset::Preload(U"gachafont");

	TextureAsset::Register(U"gachaback", U"resources/images/backs/gacha.jpg", AssetParameter::LoadAsync());

	AudioAsset::Register(U"gachahandl", U"resources/musics/items/gacha/gacha.wav", AssetParameter::LoadAsync());
	//�G�t�F�N�g�Ǘ��p�̏�����
	effects = new MyEffects();
	toast = new MyToast(U"�������b�Z�[�W�ł����ꂪ�\�������Ώ���������Ă��Ȃ�");

	//�K�`���G�t�F�N�g�̏�����
	gachaEffects = new MyEffects();
	gachaEffect = new MyImageEffect(U"resources/images/items/gacha/gachaeffect1.png", 10, 4, (const float)0.05);
	TextureAsset::Register(U"gachaeffectback2", U"resources/images/items/gacha/gacha.png");
	//�ϐ��̏�����
	button[(int)BUTTON::GACHA] = new MyImageButton(U"resources/images/items/gacha/gachabutton", U"", 30, 1700, 600);
	button[(int)BUTTON::EXIT] = new MyImageButton(U"resources/images/items/gacha/exitbutton", U"", 30, 300, 600);
	selectedButton = BUTTON::GACHA;		//�����̃{�^���I����Ԃ��K�`����
	nowGachaState = GACHA_STATE::TITLE;	//�K�`���̏�Ԃ������Ȃ���Ԃ�
}

Gacha::~Gacha(void) {//�I������
	FontAsset::Unregister(U"gachafont");
	TextureAsset::Unregister(U"gachaback");
	AudioAsset::Unregister(U"gachahandl");
	for (int i = 0; i < (int)BUTTON::SIZE; i++) {
		delete button[i];
	}
	delete backAudio;
}

bool Gacha::isReady(void) {//��������
	if (FontAsset::IsReady(U"gachafont") &&
		TextureAsset::IsReady(U"gachaback") &&
		AudioAsset::IsReady(U"gachahandl")) {
		for (int i = 0; i < (int)BUTTON::SIZE; i++) {
			if (!button[i]->isReady()) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void Gacha::start(void) {
	delete backAudio;
	backAudio = new Audio(U"resources/musics/backs/gacha.wav");
	backAudio->setLoop(true);
	backAudio->play();
}


void Gacha::update(void) {

	simpleLoadEffect->update();
	if (simpleLoadEffect->isLoad()) {
		if (simpleLoadEffect->isDark()) {
			changeNextGachaState();//�V�[���ڍs
		}
		else if(simpleLoadEffect->isEnd()){
			//���[�h����
			loadEndFunc();
		}
		else {//�Ó]��
			return;
		}
	}
	//���݂̃K�`���̏�Ԃɉ������v�Z����
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE://�{�^���I�����
		updateTitle();
		break;
	case Gacha::GACHA_STATE::EFFECT://�G�t�F�N�g
		if (gachaEffects->isEmpty()) {//��U��ɂȂ��Ă���Ȃ玟�̃K�`���G�t�F�N�g�����s����
			setNextGachaState(GACHA_STATE::RESULT);//�K�`����Ԃ��G�t�F�N�g�P��
		}
		break;
	case Gacha::GACHA_STATE::RESULT://���U���g���
		Print(U"���U���g��ʂł�");
		if (MyKey::getDecisionKey()) {
			setNextGachaState(GACHA_STATE::TITLE);//�K�`����Ԃ��G�t�F�N�g�P��
		}
		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
}

void Gacha::draw(void) {
	//�w�i�̕`��
	TextureAsset(U"gachaback").draw();

	//���݂̏�Ԃɉ�������ʕ`��
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE://�^�C�g�����
		drawButton();
		break;
	case Gacha::GACHA_STATE::EFFECT://�K�`���K�`���̃G�t�F�N�g
		if (gachaEffects->isEmpty()) {//��Ȃ�V�[���ڍs���Ȃ̂ŃK�`���̉摜��`��
			TextureAsset(U"gachaeffectback2").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		}
		else {//�G�t�F�N�g��
			gachaEffects->draw();
		}
		break;
	case Gacha::GACHA_STATE::RESULT:
		resultDraw();
		FontAsset(U"gachafont")(U"�`Press Enter�`").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 150);
		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
	//�ėp�G�t�F�N�g
	effects->draw();
	//���[�h�G�t�F�N�g
	simpleLoadEffect->draw();
	//�f�o�b�O�p
	Print(U"���݂̃|�C���g" + Format(User::getUserPoint()));
}

void Gacha::selectedMove() {//���ݑI������Ă�����̂̍X�V����
	if (MyKey::getRightKeyDown()) {
		selectedButton = BUTTON::GACHA;
	}
	if (MyKey::getLeftKeyDown()) {
		selectedButton = BUTTON::EXIT;
	}
}

void Gacha::drawButton() {//�{�^���̕`��
	switch (selectedButton)
	{
	case Gacha::BUTTON::GACHA:
		button[(int)BUTTON::GACHA]->drawNotWord(true);
		button[(int)BUTTON::EXIT]->drawNotWord();
		break;
	case Gacha::BUTTON::EXIT:
		button[(int)BUTTON::GACHA]->drawNotWord();
		button[(int)BUTTON::EXIT]->drawNotWord(true);
		break;
	}
}

void Gacha::setNextGachaState(GACHA_STATE nextState) {//�K�`���̏�Ԃ�ύX�v��
	nextGachaState = nextState;
	simpleLoadEffect->start();//���[�h�̊J�n
}

void Gacha::changeNextGachaState() {//�K�`���̏�Ԃ�ύX
	nowGachaState = nextGachaState;

	//���邭�Ȃ�n�߂鎞�ɓ��삷��
	loadBrightingFunc();
}


//���邭�Ȃ�n�߂鎞�ɓ��삷��
void Gacha::loadBrightingFunc() {
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE:
		break;
	case Gacha::GACHA_STATE::EFFECT:
		//�G�t�F�N�g��ǉ�����
		gachaEffects->add(gachaEffect, Vec2(Window::ClientWidth() / 2, Window::ClientHeight() / 2));
		//���ʉ��Đ�
		AudioAsset(U"gachahandl").setVolume(0.1);
		AudioAsset(U"gachahandl").play();
		break;
	case Gacha::GACHA_STATE::RESULT:
		
		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
}

//���[�h���I��������Ɏ��s����(���S�ɖ��邭�Ȃ������j
void Gacha::loadEndFunc() {
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE:

		break;
	case Gacha::GACHA_STATE::EFFECT:

		break;
	case Gacha::GACHA_STATE::RESULT:

		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
}


void Gacha::updateTitle() {
	if (MyKey::getDecisionKey()) {//����L�[�������ꂽ��
		switch (selectedButton)
		{
		case Gacha::BUTTON::GACHA:	//�K�`���K�`��������
			if (isPlayGacha()) {//�K�`�����v���C�ł�����
				setNextGachaState(GACHA_STATE::EFFECT);	//�K�`����Ԃ��G�t�F�N�g�P��
				User::subUserPoint(GACHA_PRICE);		//�|�C���g�����炷
				randomGacha();							//�K�`�����s��
			}
			break;
		case Gacha::BUTTON::EXIT://���[�h�I���֖߂�
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		}
	}
	selectedMove();//�I���̈ړ�����,
}

bool Gacha::isPlayGacha() {
	if (User::hasAllItem()) {
		//�S�ẴA�C�e�����擾�ς݂Ȃ̂ŃK�`�����o���Ȃ��B
		toast->setMessage(U"�擾�ł���A�C�e���͂�������܂���");
		effects->add(toast, Window::ClientCenter());
		return false;
	}
	else if (User::getUserPoint() < GACHA_PRICE) {
		//�|�C���g������Ă��Ȃ�
		toast->setMessage(U"�|�C���g������܂���");
		effects->add(toast, Window::ClientCenter());
		return false;
	}
	return true;
}

//�K�`�����s��
void Gacha::randomGacha() {
	User::getRandomGacha(itemName);
	TextureAsset::Unregister(U"gachaitem");
	TextureAsset::Register(U"gachaitem", U"resources/images/gachaitems/"+ itemName + U".png");
}

//�K�`�����ʂ̕`��
void Gacha::resultDraw() {
	TextureAsset(U"gachaitem").drawAt(Window::ClientCenter());
}