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
	TextureAsset::Register(U"landscape", U"resources/images/backs/landscape.jpg");
	TextureAsset::Register(U"motionback", U"resources/images/backs/gacha.png", AssetParameter::LoadAsync());
	//プレイヤーコンストラクタ引数
	player=DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	nowselect = ANIME;
	judge = NONE;	//NONEに変える
	ballDraw = false;
	hiteffect = new MyImageEffect(U"resources/images/items/game/dodge/effect.png",2,5);
	effects = new MyEffects();

	judgeHitSensorState();
	judgeHitOrMiss();   //HITeffect確認のためにコメントアウト中
	scoreStore();
}
DodgeHitMotion::~DodgeHitMotion() {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;

}

void DodgeHitMotion::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}

void DodgeHitMotion::update() 
{
		if (nowselect==ANIME&&MyKey::getDecisionKey()) {
			nowselect = JUDGE;
		}
		else if (nowselect == JUDGE ) {
			if (MyKey::getDecisionKey()) {
				nowselect = NEXT;
			}
			else if (judge == HIT) {//当たった瞬間だけ呼ばれるようにするif
				effects->add(hiteffect,Vec2(Window::ClientCenter()));
			}
			else if (judge == MISS) {

			}
		}
		else if (nowselect == NEXT ) {
			if (MyKey::getDecisionKey()) {
				if (ballCnt == 0) {
					setNextScene(DODGE_SCENE::RESULT);
				}
				else setNextScene(DODGE_SCENE::GAME);	//引数渡す
			}
		}

}

void DodgeHitMotion::draw() {
	TextureAsset(U"landscape").draw();

	switch (nowselect)
	{
	case DodgeHitMotion::ANIME:
		//ボールを投げる動作
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
			effects->draw();		//触らん
		}
		else if(judge == MISS){
		}
		break;

	case DodgeHitMotion::NEXT:
		TextureAsset(U"motionback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);	//残機表示？
		break;
	default:
		break;
	}

}

void DodgeHitMotion::judgeHitSensorState() {
	if (dVelocity>= 15)speed = FAST;
	else if (dVelocity >= 10)speed = NORMAL;
	else if (dVelocity >= 5)speed = LATE;
	//センサーの値で分岐（FAST,NORMAL,LATE）
}

void DodgeHitMotion::judgeHitOrMiss() {
	int calc = 100-(speed * hitLevel / 100);	//当たる確率（％換算）
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

