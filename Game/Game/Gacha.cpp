#include "Gacha.h"

constexpr int GACHA_PRICE = 500;

Gacha::Gacha(void) {
	//���[�h�G�t�F�N�g�̏�����
	simpleLoadEffect = new SimpleLoadEffect();

	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"gachafont", 70, AssetParameter::LoadAsync());
	FontAsset::Preload(U"gachafont");
	FontAsset::Register(U"gachasmallfont", 50, AssetParameter::LoadAsync());
	FontAsset::Preload(U"gachasmallfont");

	//�w�i���[�h
	TextureAsset::Register(U"gachaback", U"resources/images/backs/gacha/gacha.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"gachabackeffect", U"resources/images/backs/gacha/effect.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"gachabackresult", U"resources/images/backs/gacha/result.png", AssetParameter::LoadAsync());

	//�I�[�f�B�I�A�Z�b�g
	AudioAsset::Register(U"gachahandl", U"resources/musics/items/gacha/gacha.wav", AssetParameter::LoadAsync());
	AudioAsset::Register(U"gacharesult", U"resources/musics/items/gacha/result.wav", AssetParameter::LoadAsync());
	//�G�t�F�N�g�Ǘ��p�̏�����
	effects = new MyEffects();
	toast = new MyToast(U"�������b�Z�[�W�ł����ꂪ�\�������Ώ���������Ă��Ȃ�");

	//�K�`���G�t�F�N�g�̏�����
	gachaEffects = new MyEffects();
	gachaEffect = new MyImageEffect(U"resources/images/items/gacha/gachaeffect1.png", 10, 4, (const float)0.05);
	TextureAsset::Register(U"gachaeffectback2", U"resources/images/items/gacha/gacha.png");

	//�K�`���^�C�g���̃|�C���g�\���̔w�i
	TextureAsset::Register(U"gachapointframe", U"resources/images/items/gacha/frame.png");

	//���U���g��ʗp�摜

	//�ϐ��̏�����
	button[(int)BUTTON::GACHA] = new MyImageButton(U"resources/images/items/gacha/gachabutton", U"", 10, Scene::Width() / 2 + 450, Scene::Height() * 0.8);
	button[(int)BUTTON::EXIT] = new MyImageButton(U"resources/images/items/gacha/exitbutton", U"", 10, Scene::Width() / 2 - 450, Scene::Height() * 0.8);
	selectedButton = BUTTON::GACHA;		//�����̃{�^���I����Ԃ��K�`����
	nowGachaState = GACHA_STATE::TITLE;	//�K�`���̏�Ԃ������Ȃ���Ԃ�

	alpha = 0;

}

Gacha::~Gacha(void) {//�I������
	FontAsset::Unregister(U"gachafont");
	FontAsset::Unregister(U"gachasmallfont");
	TextureAsset::Unregister(U"gachaback");
	TextureAsset::Unregister(U"gachabackeffect");
	TextureAsset::Unregister(U"gachabackresult");
	TextureAsset::Unregister(U"gachaeffectback2");
	TextureAsset::Unregister(U"gachapointframe");

	TextureAsset::Unregister(U"gachaitem");
	TextureAsset::Unregister(U"gachatext");

	AudioAsset::Unregister(U"gachahandl");
	AudioAsset::Unregister(U"gacharesult");

	for (int i = 0; i < (int)BUTTON::SIZE; i++) {
		delete button[i];
	}
	delete backAudio;
}

bool Gacha::isReady(void) {//��������
	if (FontAsset::IsReady(U"gachafont") &&
		FontAsset::IsReady(U"gachasmallfont")&&
		TextureAsset::IsReady(U"gachaback") &&
		TextureAsset::IsReady(U"gachabackeffect") &&
		TextureAsset::IsReady(U"gachabackresult") &&
		TextureAsset::IsReady(U"gachaeffectback2") &&
		TextureAsset::IsReady(U"gachapointframe") &&
		AudioAsset::IsReady(U"gachahandl") &&
		AudioAsset::IsReady(U"gacharesult")) {
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
	backAudio->setVolume(0.1);
	backAudio->setLoop(true);
	backAudio->play();
}


void Gacha::update(void) {

	simpleLoadEffect->update();
	if (simpleLoadEffect->isLoad()) {
		if (simpleLoadEffect->isDark()) {
			simpleLoadEffect->nextState();//��Ԉڍs DARK��DARK_WAIT
			simpleLoadEffect->nextState();//��Ԉڍs DARK_WAIT �� BRIGHTING
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
			GeneralSoundEffects::play(SE_NAME::DECISION);
			setNextGachaState(GACHA_STATE::TITLE);//�K�`����Ԃ��G�t�F�N�g�P��
		}
		changeAlpha();
		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
}

void Gacha::draw(void) {
	//�w�i�̕`��

	//���݂̏�Ԃɉ�������ʕ`��
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE://�^�C�g�����
		TextureAsset(U"gachaback").draw();
		TextureAsset(U"gachapointframe").drawAt(350, 100);
		FontAsset(U"gachasmallfont")(U"����" + Format(User::getUserPoint()) + U"P").drawAt(350, 100,ColorF(0,0,0));
		drawButton();
		break;
	case Gacha::GACHA_STATE::EFFECT://�K�`���K�`���̃G�t�F�N�g
		TextureAsset(U"gachabackeffect").drawAt(Scene::Center());
		if (gachaEffects->isEmpty()) {//��Ȃ�V�[���ڍs���Ȃ̂ŃK�`���̉摜��`��
			TextureAsset(U"gachaeffectback2").drawAt(Scene::Width() / 2, Scene::Height() / 2);
		}
		else {//�G�t�F�N�g��
			gachaEffects->draw();
		}
		break;
	case Gacha::GACHA_STATE::RESULT:
		TextureAsset(U"gachabackresult").draw();
		Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(1, 1, 1, 0.5));
		resultDraw();
		FontAsset(U"gachafont")(U"�`Press to Enter�`").drawAt(Scene::Width() / 2, Scene::Height() - 100, ColorF(0,0,0, alpha));

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
		//���ʉ��Đ�
		GeneralSoundEffects::play(SE_NAME::CURSOR);
		selectedButton = BUTTON::GACHA;
	}
	if (MyKey::getLeftKeyDown()) {
		//���ʉ��Đ�
		GeneralSoundEffects::play(SE_NAME::CURSOR);
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
		backAudio->pause();//BGM�ꎞ��~
		//�G�t�F�N�g��ǉ�����
		gachaEffects->add(gachaEffect, Vec2(Scene::Width() / 2, Scene::Height() / 2));
		//���ʉ��Đ�
		AudioAsset(U"gachahandl").setVolume(0.1);
		AudioAsset(U"gachahandl").play();
		break;
	case Gacha::GACHA_STATE::RESULT:
		backAudio->play();
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
		//���ʉ��Đ�
		AudioAsset(U"gacharesult").setVolume(0.1);
		AudioAsset(U"gacharesult").play();
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
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}
	selectedMove();//�I���̈ړ�����,
}

bool Gacha::isPlayGacha() {
	if (User::hasAllItem()) {
		//�S�ẴA�C�e�����擾�ς݂Ȃ̂ŃK�`�����o���Ȃ��B
		toast->setMessage(U"�擾�ł���A�C�e���͂�������܂���");
		effects->add(toast, Scene::Center());
		return false;
	}
	else if (User::getUserPoint() < GACHA_PRICE) {
		//�|�C���g������Ă��Ȃ�
		toast->setMessage(U"�|�C���g������܂���");
		effects->add(toast, Scene::Center());
		return false;
	}
	return true;
}

//�K�`�����s��
void Gacha::randomGacha() {
	int key;
	GAME_TYPE type;
	CSVData csv;

	User::getRandomGacha(itemName, key, type);
	TextureAsset::Unregister(U"gachaitem");
	TextureAsset::Register(U"gachaitem", U"resources/images/gachaitems/"+ itemName + U".png");
	
	TextureAsset::Unregister(U"gachatext");
	TextureAsset::Register(U"gachatext", U"resources/images/gachaitems/description/" + itemName + U".png");
}

//�K�`�����ʂ̕`��
void Gacha::resultDraw() {
	TextureAsset(U"gachaitem").scaled(1.2).drawAt(Scene::Width() * 0.3, Scene::Height() * 0.6 - 130);
	TextureAsset(U"gachatext").scaled(1).drawAt(Scene::Width() * 0.7, Scene::Height() * 0.5 );
}

void Gacha::changeAlpha(void) {
	constexpr int CYCLE = 3000;//���߂��ς�����
	const uint64 t = Time::GetMillisec();
	alpha = Sin(t % CYCLE / static_cast<double>(CYCLE)* s3d::Math::Constants::TwoPi) * 0.42 + 0.58;
}