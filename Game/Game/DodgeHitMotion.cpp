#include"DodgeHitMotion.h"


DodgeHitMotion::DodgeHitMotion(DODGE_SCENE* nextScene, int ballCnt,float dVelocity,int hitLevel,struct Score score) :DodgeSceneBase(nextScene) {
	this->ballCnt = ballCnt;
	this->dVelocity = dVelocity;
	this->hitLevel = hitLevel; 
	this->score = score;
	pSpawn = Vec2(850,700);
	bSpawn = Vec2(1150,650);
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	TextureAsset::Register(U"landscape", U"resources/images/backs/landscape.jpg");
	TextureAsset::Register(U"motionback", U"resources/images/backs/gacha.png", AssetParameter::LoadAsync());
	//�v���C���[�R���X�g���N�^����
	player=DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	nowselect = ANIME;
	judge = NONE;
	ballDraw = false;

	judgeHitSensorState();
	judgeHitOrMiss();

}
DodgeHitMotion::~DodgeHitMotion() {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;
}

void DodgeHitMotion::start(void) {	//���[�h�󂯂���Ɏ��s��������
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}

void DodgeHitMotion::update() 
{
		if (nowselect==ANIME&&MyKey::getDecisionKey()) {
			nowselect = JUDGE;
		}

		else if (nowselect == JUDGE) {
				ballCnt--;
				nowselect = NEXT;
		}
		
		else if (nowselect == NEXT ) {
			if (MyKey::getDecisionKey()) {
				if (ballCnt == 0) {
					setNextScene(DODGE_SCENE::RESULT);
				}
				else setNextScene(DODGE_SCENE::GAME);	//�����n��
			}
		}	
}

void DodgeHitMotion::draw() {
	TextureAsset(U"landscape").draw();

	switch (nowselect)
	{
	case DodgeHitMotion::ANIME:
		//�{�[���𓊂��铮��
		if (!player.drawCompletecheck()) {
			player.draw();
			if (player.isBallThrow()) {
				ballDraw = true;
			}
			player.ChangeChip();
		}
		if (ballDraw==true) {
			player.draw();
			ball.Draw();
			ball.Move();
		}
		break;

	case DodgeHitMotion::JUDGE:
		if (judge == HIT) {
		
		}
		else if(judge == MISS){
		}
		break;

	case DodgeHitMotion::NEXT:
		TextureAsset(U"motionback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);	//�c�@�\���H
		break;
	default:
		break;
	}

}

void DodgeHitMotion::judgeHitSensorState() {
	if (dVelocity>= 15)speed = FAST;
	else if (dVelocity >= 10)speed = NORMAL;
	else if (dVelocity >= 5)speed = LATE;
	//�Z���T�[�̒l�ŕ���iFAST,NORMAL,LATE�j
}

void DodgeHitMotion::judgeHitOrMiss() {
	int calc = 100-(speed * hitLevel / 100);	//������m���i�����Z�j
	int border = (Random(0, 100));
	if (border >= calc)judge = HIT;
	else judge = MISS;
}

int DodgeHitMotion::getBallCnt() {
	return ballCnt;
}

struct DodgeHitMotion::getScore() {
	return score;
}

