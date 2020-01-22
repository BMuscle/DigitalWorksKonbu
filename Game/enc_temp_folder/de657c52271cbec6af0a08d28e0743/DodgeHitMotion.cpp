#include"DodgeHitMotion.h"


DodgeHitMotion::DodgeHitMotion(DODGE_SCENE* nextScene, int ballCnt,float dVelocity,int hitLevel) :DodgeSceneBase(nextScene) {
	this->ballCnt = ballCnt;
	this->dVelocity = dVelocity;
	this->hitLevel = hitLevel; 
	
	pSpawn = Vec2(200,800);
	bSpawn = Vec2(1500,250);
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	TextureAsset::Register(U"landscape", U"resources/images/backs/landscape.jpg");
	TextureAsset::Register(U"motionback", U"resources/images/backs/gacha.png", AssetParameter::LoadAsync());
	//プレイヤーコンストラクタ引数
	player = DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	nowselect = ANIME;
	judge = NONE;

	judgeHitSensorState();
	judgeHitOrMiss();

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

		else if (nowselect == JUDGE) {
				ballCnt--;
				nowselect = NEXT;
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
				
			}
			player.ChangeChip();
			ball.Draw();
		}
		break;

	case DodgeHitMotion::JUDGE:
		if (judge == HIT) {
		
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

