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
	//プレイヤーコンストラクタ引数
	player=DodgePlayer(pSpawn, U"resources/images/items/game/dodge/player.png");
	ball = Ball(bSpawn, U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	ballJudge = Ball(Vec2(Window::ClientWidth()*0.5,Window::ClientHeight()), U"resources/images/items/game/dodge/ball.png", this->dVelocity);
	targetJudge = DodgeCharacter(Vec2(Window::ClientCenter()), U"resources/images/items/game/dodge/target.png");
	nowselect = ANIME;
	judge =HIT;	//NONEに変える
	ballDraw = false;
	hiteffect = new MyImageEffect(U"resources/images/items/game/dodge/effect.png",2,5);
	effects = new MyEffects();
	frameWait = 0;

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
		if (nowselect==ANIME&&frameWait>=170) {
			frameWait = 0;
			nowselect = JUDGE;
		}
		else if (nowselect == JUDGE ) {	//現在の状態がジャッジ
			if (frameWait==110) {//取りま今だけ
				frameWait = 0;
				nowselect = NEXT;
			}
			if (judge == HIT) {//当たった瞬間だけ呼ばれるようにするif
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
		
		else if (nowselect == NEXT ) {	//次のシーンへ移行する
			
				if (ballCnt == 0) {
					setNextScene(DODGE_SCENE::RESULT);
				}
				else setNextScene(DODGE_SCENE::GAME);	//引数渡す
			
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
		mainFont(U"加速度").drawAt(250, 100, Color(255, 102, 0));
		mainFont(U"命中率").drawAt(250, 410, Color(255, 102, 0));
		subFont(Format(dVelocity) +U"m/s2").drawAt(405,250, Color(0,0,0));
		subFont(Format(hitLevel) + U"%").drawAt(400, 560, Color(0, 0, 0));
		frameWait++;
		break;

	case DodgeHitMotion::JUDGE:
		
		if (judge == HIT) {
			mainFont(U"HIT").drawAt(300, 400, Color(255, 51, 0));
			//ターゲット描画
			targetJudge.targetHitDraw(0, 1);
			//エフェクト描画
			//if () {
				effects->draw();		//触らん
			//}
			//ボール描画
			ballJudge.BallHitDraw();
			
		}
		else if(judge == MISS){
			mainFont(U"MISS").drawAt(300, 400, Color(0, 153, 255));
			//ターゲット描画
			targetJudge.targetMissDraw();
			//エフェクト描画なし
			//ボール描画
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

