#include"DodgeHitMotion.h"


DodgeHitMotion::DodgeHitMotion(DODGE_SCENE* nextScene, int ballCnt,float dVelocity,int hitLevel,struct Score score) :DodgeSceneBase(nextScene) {
	this->ballCnt = ballCnt-1;
	this->dVelocity = dVelocity;
	this->hitLevel = hitLevel; 
	this->score = score;
	pSpawn = Vec2(850,700);
	bSpawn = Vec2(1150,650);
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	subFont = Font(200, U"resources/font/kokuban.ttf");
	mainFont = Font(150, U"resources/font/RiiPopkkR.otf");
	TextureAsset::Register(U"landscape", U"resources/images/backs/landscape.jpg");
	TextureAsset::Register(U"motionback", U"resources/images/backs/gacha.png", AssetParameter::LoadAsync());
	//�v���C���[�R���X�g���N�^����
	player=DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	ballJudge = Ball(Vec2(Window::ClientWidth()*0.5,Window::ClientHeight()), U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	targetJudge = DodgeCharacter(Vec2(Window::ClientCenter()), U"resources/images/items/game/dodge/target.png");
	nowselect = ANIME;
	judge = NONE;	//NONE�ɕς���
	ballDraw = false;
	hiteffect = new MyImageEffect(U"resources/images/items/game/dodge/effect.png",2,5);
	effects = new MyEffects();

	judgeHitSensorState();
	//judgeHitOrMiss();   //HITeffect�m�F�̂��߂ɃR�����g�A�E�g��
	scoreStore();
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
		else if (nowselect == JUDGE ) {	//���݂̏�Ԃ��W���b�W
			if (MyKey::getDecisionKey()) {//���܍�����
				nowselect = NEXT;
			}
			if (judge == HIT) {//���������u�Ԃ����Ă΂��悤�ɂ���if
				effects->add(hiteffect, Vec2(Window::ClientCenter()));
				ballJudge.BallHitUpdate();
			}
			else if (judge == MISS) {
				 targetJudge.targetMissUpdate();
				 ballJudge.BallMissUpdate();
			}
		}
		
		else if (nowselect == NEXT ) {	//���̃V�[���ֈڍs����
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
		mainFont(U"�����x").drawAt(300, 100, Color(255, 182, 193));
		mainFont(U"������").drawAt(300, 400, Color(255, 182, 193));
		subFont(Format(dVelocity)).drawAt(400,250, Color(153, 255, 255));
		subFont(Format(hitLevel)).drawAt(400, 550, Color(153, 255, 255));
		break;

	case DodgeHitMotion::JUDGE:
		
		if (judge == HIT) {
			mainFont(U"HIT").drawAt(300, 400, Color(255, 182, 193));
			//�^�[�Q�b�g�`��
			targetJudge.targetHitDraw(0, 1);
			//�G�t�F�N�g�`��
			effects->draw();		//�G���
			//�{�[���`��
			ballJudge.BallHitDraw();
			
		}
		else if(judge == MISS){
			mainFont(U"MISS").drawAt(300, 400, Color(255, 182, 193));
			//�^�[�Q�b�g�`��
			targetJudge.targetMissDraw();
			//�G�t�F�N�g�`��Ȃ�
			//�{�[���`��
			ballJudge.BallMissDraw();
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

struct Score DodgeHitMotion::getScore() {
	return score;
}

void DodgeHitMotion::scoreStore() {
	score.hit[DEFAULT - (ballCnt+1)] = judge;
	score.hitLevel[DEFAULT - (ballCnt + 1)] = hitLevel;
	score.dVelocity[DEFAULT - (ballCnt + 1)] = dVelocity;

}

