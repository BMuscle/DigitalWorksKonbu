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
	//プレイヤーコンストラクタ引数
	player=DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	ballJudge = Ball(Vec2(Window::ClientWidth()*0.5,Window::ClientHeight()), U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	targetJudge = DodgeCharacter(Vec2(Window::ClientCenter()), U"resources/images/items/game/dodge/target.png");
	nowselect = ANIME;
	judge = NONE;	//NONEに変える
	ballDraw = false;
	hiteffect = new MyImageEffect(U"resources/images/items/game/dodge/effect.png",2,5);
	effects = new MyEffects();

	judgeHitSensorState();
	//judgeHitOrMiss();   //HITeffect確認のためにコメントアウト中
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
		else if (nowselect == JUDGE ) {	//現在の状態がジャッジ
			if (MyKey::getDecisionKey()) {//取りま今だけ
				nowselect = NEXT;
			}
			if (judge == HIT) {//当たった瞬間だけ呼ばれるようにするif
				effects->add(hiteffect, Vec2(Window::ClientCenter()));
				ballJudge.BallHitUpdate();
			}
			else if (judge == MISS) {
				 targetJudge.targetMissUpdate();
				 ballJudge.BallMissUpdate();
			}
		}
		
		else if (nowselect == NEXT ) {	//次のシーンへ移行する
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
		mainFont(U"加速度").drawAt(300, 100, Color(255, 182, 193));
		mainFont(U"命中率").drawAt(300, 400, Color(255, 182, 193));
		subFont(Format(dVelocity)).drawAt(400,250, Color(153, 255, 255));
		subFont(Format(hitLevel)).drawAt(400, 550, Color(153, 255, 255));
		break;

	case DodgeHitMotion::JUDGE:
		
		if (judge == HIT) {
			mainFont(U"HIT").drawAt(300, 400, Color(255, 182, 193));
			//ターゲット描画
			targetJudge.targetHitDraw(0, 1);
			//エフェクト描画
			effects->draw();		//触らん
			//ボール描画
			ballJudge.BallHitDraw();
			
		}
		else if(judge == MISS){
			mainFont(U"MISS").drawAt(300, 400, Color(255, 182, 193));
			//ターゲット描画
			targetJudge.targetMissDraw();
			//エフェクト描画なし
			//ボール描画
			ballJudge.BallMissDraw();
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

