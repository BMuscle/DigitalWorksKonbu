#include "ShoeKickGame.h"

#define FPS 60

#define METER_WEIGHT 0.01

#define KICK_COUNT 3

//�����[�g���u���ɕ\�����邩
#define SIGNBOARD_INTERVAL 100

ShoeKickGame::ShoeKickGame(SHOEKICK_SCENE* scenep) : ShoeKickSceneBase(scenep) {
	//�����Ă���A�C�e�����i�[
	for (int i = 0; i < (int)GACHA_ITEM::SIZE; i++) {
		hasItems.push_back(User::getHasItems(GAME_TYPE::SHOEKICK, i + 1));
	}
	//�摜�̃��[�h
	TextureAsset::Register(U"shoekick_game", U"resources/images/backs/game/shoekick/game.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_frame", U"resources/images/items/game/shoekick/game/frame.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_signboard", U"resources/images/items/game/shoekick/game/signboard.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_description", U"resources/images/items/game/shoekick/game/description.png", AssetParameter::LoadAsync());

	FontAsset::Register(U"shoekick_font", 70);
	FontAsset::Preload(U"shoekick_font");

	FontAsset::Register(U"shoekick_boardfont", 70);
	FontAsset::Preload(U"shoekick_boardfont");

	countTexture[3] = new Texture(U"resources/images/items/game/shoekick/game/count/3.png");
	countTexture[2] = new Texture(U"resources/images/items/game/shoekick/game/count/2.png");
	countTexture[1] = new Texture(U"resources/images/items/game/shoekick/game/count/1.png");
	countTexture[0] = new Texture(U"resources/images/items/game/shoekick/game/count/kick.png");

	kickPower = 0;
	kickCount = 1000;

	nowGameState = KICK;
	nextGameState = KICK;

	isStart = false;



	boardVec.push_back(createSignBoard(0));
	boardVec.push_back(createSignBoard(50));
	boardVec.push_back(createSignBoard(100));
	boardVec.push_back(createSignBoard(150));
	boardVec.push_back(createSignBoard(200));
	boardVec.push_back(createSignBoard(250));
	boardVec.push_back(createSignBoard(300));
	boardVec.push_back(createSignBoard(350));
	boardVec.push_back(createSignBoard(400));
	boardVec.push_back(createSignBoard(450));
	boardVec.push_back(createSignBoard(500));
	boardVec.push_back(createSignBoard(550));
	boardVec.push_back(createSignBoard(600));
	boardVec.push_back(createSignBoard(650));
	boardVec.push_back(createSignBoard(700));

	character = new ShoeCharacter(Vec2(0,GROUND));
	shoe = new Shoe(&hasItems);

	frameCnt = 0;

	isDescription = true;

}
ShoeKickGame::~ShoeKickGame() {
	delete backAudio;

	TextureAsset::Unregister(U"shoekick_game");
	TextureAsset::Unregister(U"shoekick_frame");
	TextureAsset::Unregister(U"shoekick_signboard");
	TextureAsset::Unregister(U"shoekick_description");

	FontAsset::Unregister(U"shoekick_font");
	FontAsset::Unregister(U"shoekick_boardfont");

	for (int i = 0; i < 4; i++) {
		delete countTexture[i];
	}
	delete character;
	delete shoe;
}

bool ShoeKickGame::isReady(void) {
	if (TextureAsset::IsReady(U"shoekick_description")) {
		return true;
	}
	return false;
}

void ShoeKickGame::start(void) {
	isStart = true;

	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/shoekick/game.wav");
	backAudio->setLoop(true);
	backAudio->play();

	//�L�b�N����n�܂�̂Ń^�C�}�[start�]���P�b
	setKickTimer(FPS * (KICK_COUNT + 1.5));
}

void ShoeKickGame::update(void) {
	if (isDescription) {//�������
		if (MyKey::getDecisionKey()) {
			isDescription = false;
			GeneralSoundEffects::play(SE_NAME::DECISION);
		}
		return;
	}

	if (nowGameState != nextGameState) {
		changeState();
	}

	switch (nowGameState)
	{
	case ShoeKickGame::KICK:
		updateKick();
		if (kickCount / FPS < KICK_COUNT) {
			character->setMoveRight();
		}
		break;
	case ShoeKickGame::FLY:
		updateFly();
		character->setVecMoveLeft(Window::ClientWidth() / 2 - shoe->getTotalVec().x);
		break;
	case ShoeKickGame::END:
		frameCnt--;
		character->setVecMoveLeft(Window::ClientWidth() / 2 - shoe->getTotalVec().x);
		if (frameCnt < 0) {
			setNextScene(SHOEKICK_SCENE::RESULT);
		}
		break;
	}

	character->update();

}

void ShoeKickGame::draw(void) {
	int x = Window::ClientWidth() / 2 - ((int)shoe->getTotalVec().x % Window::ClientWidth());
	//�w�i�`��
	TextureAsset(U"shoekick_game").drawAt(x, Window::ClientHeight() / 2);
	TextureAsset(U"shoekick_game").drawAt(x + Window::ClientWidth(), Window::ClientHeight() / 2);


	//METER�`��
	int meter = (int)(shoe->getTotalVec().x * METER_WEIGHT);
	Rect tmp = FontAsset(U"shoekick_font")(Format(meter) + U"M").boundingRect();			//���W�n����
	TextureAsset(U"shoekick_frame").draw(500 - 450, 100 + 0);	//�t���[���`��
	FontAsset(U"shoekick_font")(Format(meter) + U"m").draw(500 - tmp.w,100,ColorF(0,0,0,1));//�����`��
	//�Ŕ`��
	for (auto vec : boardVec) {
		TextureAsset(U"shoekick_signboard").drawAt(vec.vec.x - shoe->getTotalVec().x, vec.vec.y);
		FontAsset(U"shoekick_boardfont")(Format(vec.meter)).drawAt(vec.vec.x - shoe->getTotalVec().x, vec.vec.y, ColorF(0, 0, 0));
	}
	//Character�`��
	character->draw();


	switch (nowGameState)
	{
	case ShoeKickGame::KICK:
		drawKick();
		break;
	case ShoeKickGame::FLY:
		drawFly();
		break;
	case ShoeKickGame::END:
		drawFly();
	}
	//��������`��
	if (isDescription) {
		Rect(0, 0, Window::ClientWidth(), Window::ClientHeight()).draw(ColorF(1, 1, 1, 0.8));
		TextureAsset(U"shoekick_description").drawAt(Window::ClientCenter());
	}
}

void ShoeKickGame::setNextState(GAME_STATE next) {
	nextGameState = next;
}

void ShoeKickGame::changeState() {
	nowGameState = nextGameState;
}


void ShoeKickGame::updateKick() {
	constexpr int KICKINTERVAL = FPS * 1;//�R����󂯕t���鎞��
	updateKickTimer();
	if (kickCount > 0) {//�J�E���g�_�E����
		if (kickCount % FPS == 0) {
			//���ʉ��炷

		}
	}
	else if (kickCount == -54) {
		character->setMoveJump();
	}
	else if (kickCount > -KICKINTERVAL) {//�J�E���g�_�E�����I�������̂ŃL�b�N����
		Vec3 acc = Sensor::getAcceleration();
	
		//�u�ԉ����x�ő�l���擾
		if (kickPower < abs(acc.x)) {
			kickPower = abs(acc.x);
		}
	}
	else {//�L�b�N���ԉ���
		setNextState(FLY);//�V�[���ڍs����
		if (kickPower <= 0) {
			kickPower = 20.0;
		}
		shoe->setShoeVector(kickPower);//�C��΂��̃p���[�����߂�B
	}
}

void ShoeKickGame::drawKick() {
	if (isStart) {
		drawKickTimer();
	}
}

void ShoeKickGame::updateFly() {
	if (!shoe->update()) {
		setNextState(GAME_STATE::END);
		frameCnt = 100;
	}
}

void ShoeKickGame::drawFly() {
	//�C�`��
	shoe->draw();
}

//�R�鎞�̃J�E���g�_�E��
void ShoeKickGame::updateKickTimer() {
	kickCount--;
}

//�R�鎞�̃J�E���g�_�E���`��
void ShoeKickGame::drawKickTimer() {
	int cnt = kickCount / FPS + 1;
	if (cnt > 3) {
		return;
	}
	if (kickCount > 0) {
		//�����`��
		countTexture[cnt]->drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
	}
	else {
		//�R��I��`��
		countTexture[0]->drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
	}
}

//�R�鎞�̃J�E���g�_�E���Z�b�g
void ShoeKickGame::setKickTimer(int kicktime) {
	kickCount = kicktime;
}

ShoeKickGame::SignBoard ShoeKickGame::createSignBoard(int meter) {
	SignBoard board;
	if (meter == 0) {
		board.vec = Vec2(Window::ClientWidth() /2, GROUND - 120);
	}
	else {
		board.vec = Vec2(Window::ClientWidth() / 2 + meter / METER_WEIGHT , GROUND - 120);
	}
	board.meter = meter;
	return board;
}

int ShoeKickGame::getMeter() {
	return shoe->getTotalVec().x * METER_WEIGHT;
}