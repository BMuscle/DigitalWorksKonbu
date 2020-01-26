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
	subFont = Font(180, U"resources/font/RiiPopkkR.otf");
	mainFont = Font(130, U"resources/font/RiiPopkkR.otf");
	TextureAsset::Register(U"landscape", U"resources/images/backs/landscape.jpg");
	TextureAsset::Register(U"motionback", U"resources/images/backs/gacha.png", AssetParameter::LoadAsync());
	//�v���C���[�R���X�g���N�^����
	player=DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	ballJudge = Ball(Vec2(Window::ClientWidth()*0.5,Window::ClientHeight()), U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	targetJudge = DodgeCharacter(Vec2(Window::ClientCenter()), U"resources/images/items/game/dodge/target.png");
	nowselect = ANIME;
	judge =HIT;	//NONE�ɕς���
	ballDraw = false;
	hiteffect = new MyImageEffect(U"resources/images/items/game/dodge/effect.png",2,5);
	effects = new MyEffects();
	frameWait = 0;

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
		if (nowselect==ANIME&&frameWait>=170) {
			frameWait = 0;
			nowselect = JUDGE;
		}
		else if (nowselect == JUDGE ) {	//���݂̏�Ԃ��W���b�W
			if (frameWait==110) {//���܍�����
				frameWait = 0;
				nowselect = NEXT;
			}
			if (judge == HIT) {//���������u�Ԃ����Ă΂��悤�ɂ���if
				if (ballJudge.HitCheck()) {
					effects->add(hiteffect, Vec2(Window::ClientCenter()));
				}
				ballJudge.BallHitUpdate();
			}
			else if (judge == MISS) {
				 targetJudge.targetMissUpdate();
				 ballJudge.BallMissUpdate();
			}
		}
		
		else if (nowselect == NEXT ) {	//���̃V�[���ֈڍs����
			
				if (ballCnt == 0) {
					setNextScene(DODGE_SCENE::RESULT);
				}
				else setNextScene(DODGE_SCENE::GAME);	//�����n��
			
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
		mainFont(U"�����x").drawAt(250, 100, Color(255, 102, 0));
		mainFont(U"������").drawAt(250, 410, Color(255, 102, 0));
		subFont(Format(dVelocity) +U"m/s2").drawAt(405,250, Color(0,0,0));
		subFont(Format(hitLevel) + U"%").drawAt(400, 560, Color(0, 0, 0));
		frameWait++;
		break;

	case DodgeHitMotion::JUDGE:
		
		if (judge == HIT) {
			mainFont(U"HIT").drawAt(300, 400, Color(255, 51, 0));
			//�^�[�Q�b�g�`��
			targetJudge.targetHitDraw(0, 1);
			//�G�t�F�N�g�`��
			//if () {
				effects->draw();		//�G���
			//}
			//�{�[���`��
			ballJudge.BallHitDraw();
			
		}
		else if(judge == MISS){
			mainFont(U"MISS").drawAt(300, 400, Color(0, 153, 255));
			//�^�[�Q�b�g�`��
			targetJudge.targetMissDraw();
			//�G�t�F�N�g�`��Ȃ�
			//�{�[���`��
			ballJudge.BallMissDraw();
		}
		frameWait++;
		break;

	default:
		break;
	}

}

void DodgeHitMotion::judgeHitSensorState() {
	if (dVelocity>= 30)speed = FAST;
	else if (dVelocity >= 20)speed = NORMAL;
	else if (dVelocity >= 15)speed = LATE;
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

