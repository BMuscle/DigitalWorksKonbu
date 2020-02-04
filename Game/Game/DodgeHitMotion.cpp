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
	judgeFont = Font(220, U"resources/font/RiiPopkkR.otf");
	TextureAsset::Register(U"landscape", U"resources/images/backs/landscape.jpg");
	TextureAsset::Register(U"motionback", U"resources/images/backs/gacha.png");
	//�v���C���[�R���X�g���N�^����
	player=DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	ballJudge = Ball(Vec2(Window::ClientWidth()*0.5,Window::ClientHeight()), U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	targetJudge = DodgeCharacter(Vec2(Window::ClientCenter()), U"resources/images/items/game/dodge/target.png");
	nowselect = ANIME;
	judge =NONE;	//NONE�ɕς���
	ballDraw = false;
	hiteffect = new MyImageEffect(U"resources/images/items/game/dodge/effect.png",2,5);
	effects = new MyEffects();
	frameWait = 0;
	fontOn = false;
	effectFlag = false;
	sFlag=false;
	sFlag1 = false;
	sFlag2 = false;

	judgeHitSensorState();
	judgeHitOrMiss();   //HITeffect�m�F�̂��߂ɃR�����g�A�E�g��
	scoreStore();
	AudioAsset::Register(U"hit", U"resources/musics/items/game/dodge/hit.wav");
	AudioAsset::Register(U"throw", U"resources/musics/items/game/dodge/throw.wav");
	AudioAsset::Register(U"escape", U"resources/musics/items/game/dodge/escape.wav");


}
DodgeHitMotion::~DodgeHitMotion() {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	AudioAsset::Unregister(U"filename");
	AudioAsset::Unregister(U"hit");
	AudioAsset::Unregister(U"throw");
	AudioAsset::Unregister(U"escape");
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
		if (nowselect==ANIME&&frameWait>=150) {
			frameWait = 0;
			nowselect = JUDGE;
		}
		else if (nowselect == JUDGE ) {	//���݂̏�Ԃ��W���b�W
			if (frameWait==120) {
				frameWait = 0;
				nowselect = NEXT;
			}
			if (judge == HIT) {//���������u�Ԃ����Ă΂��悤�ɂ���if
				if (ballJudge.HitCheck()) {
					if (!effectFlag) {
						effects->add(hiteffect, Vec2(Window::ClientCenter()));
						effectFlag = true;
					}
					fontOn = true;
				}
				ballJudge.BallHitUpdate();
			}
			else if (judge == MISS) {
				if (ballJudge.HitCheck()) {
					fontOn = true;
				}
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
			if (!sFlag) {
				sFlag = true;
				AudioAsset(U"throw").setPosSec(0);
				AudioAsset(U"throw").setVolume(0.3);
				AudioAsset(U"throw").play();
			}

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
			if(fontOn)judgeFont(U"HIT").drawAt(300, 350, Color(255, 51, 0));
			//�^�[�Q�b�g�`��
			targetJudge.targetHitDraw(0, 1);
			//�G�t�F�N�g�`��
			//if () {
				effects->draw();
				if (effectFlag&&!sFlag2) {
					sFlag2 = true;
					AudioAsset(U"hit").setPosSec(0);
					AudioAsset(U"hit").setVolume(0.1);
					AudioAsset(U"hit").play();//�G���
				}
			//}
			//�{�[���`��
			ballJudge.BallHitDraw();
			
		}
		else if(judge == MISS){
			if(fontOn)judgeFont(U"MISS").drawAt(300, 350, Color(0, 153, 255));
			//�^�[�Q�b�g�`��
			targetJudge.targetMissDraw();
			if (!sFlag1) {
				sFlag1 = true;
				AudioAsset(U"escape").setPosSec(0);
				AudioAsset(U"escape").setVolume(0.1);
				AudioAsset(U"escape").play();
			}
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
	if (judge == HIT)score.hit[DEFAULT - (ballCnt + 1)] = true;
	else score.hit[DEFAULT - (ballCnt+1)] = false;
	score.hitLevel[DEFAULT - (ballCnt + 1)] = hitLevel;
	score.dVelocity[DEFAULT - (ballCnt + 1)] = dVelocity;

}

