#include"DodgeGame.h"
#include"MyKey.h"

DodgeGame::DodgeGame(DODGE_SCENE* nextScene, int ballCnt) :DodgeSceneBase(nextScene) {
	this->ballCnt = ballCnt;

	spawn = Vec2(340, 60);
	scope = Scope(50, spawn);
	ballplace = Vec2(1500, 960);

	TextureAsset::Register(U"rule",U"resources/images/backs/rule.jpg");
	TextureAsset::Register(U"landscape",U"resources/images/items/game/dodge/gameback.png");
	if (ballCnt == DEFAULT) {
		nowselect=RULE;
	}
	else {
		nowselect = GAME;
	}

	//ゲームスタート！（文字）（効果音）


	//配列に入れる処理
	for (int i = 0; i < 5; i++) {
		mobs.push_back(DodgeCharacter(Vec2(Random(AREA_LEFT, AREA_RIGHT), Random(AREA_UP, AREA_DOWN)), U"resources/images/items/game/dodge/mob.png"));
	}
	for (int i = 0; i < ballCnt; i++) {
		balllife.push_back( BallLife(ballplace, U"resources/images/items/game/dodge/balllife.png", i));
	}
	target = DodgeCharacter(Vec2(480, 450), U"resources/images/items/game/dodge/target.png");
	Scopeimage = Texture(U"resources/images/backs/Scopeimage.png");

}

DodgeGame::~DodgeGame()
{

}

void DodgeGame::start(void)
{
	//BGMとかフラグをオンにする
	//暗転が明けてから一回だけ実行される処理
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}

void DodgeGame::update()
{
	if (nowselect == START) {
		nowselect = RULE;
	}
	else if (nowselect == RULE && MyKey::getDecisionKey() ) {
		nowselect = GAME;
	}
	else if (nowselect == GAME) {
		//場所のセット 
		target.Move(movement);
		
		for (auto& mob : mobs) {
			mob.Move(movement);
		}
		scope.setPlace(scope.getPlace() + Vec2(0, 20));//更新処理update
		Circle scopeimage(scope.getPlace(), scope.getRadius());


		//物理当たり判定チェック
		if (getHitSensorState()||MyKey::getDecisionKey()) {
			//画面上当たり判定チェック
			hitLevel = HitScopeCheck(scope.getRadius(), scope.getPlace(), target.getRadius() - 25, target.getPlace());//スコープ、ターゲット
			nowselect = MOTION;
		}

		//再描画
		if (scope.getPlace().y > Window::ClientHeight() ) {//下まで行ったら
			scope.setPlace(Vec2(scope.getPlace().x + 30, -50));
		}
		if (scope.getPlace().x > Window::ClientHeight()) {
			scope.setPlace(Vec2(-50, scope.getPlace().y));
		}
	}

	else if (nowselect == MOTION)
	{
		setNextScene(DODGE_SCENE::MOTION);
	}
	
}

void DodgeGame::draw()
{
	switch (nowselect)
	{
		case START:
			break;
		case RULE:
			TextureAsset(U"rule").draw();
			break;
		case GAME:
			TextureAsset(U"landscape").draw();
			
			//ターゲットの描写
			target.draw();
			
			//モブの描写
			for (auto& mob : mobs) {
				mob.draw();
			}
			//スコープの描写
			Scopeimage.drawAt(scope.getPlace());//描画処理draw

			//ボールの残機表示
			for (auto& balllife : balllife) {
				balllife.Draw();
			}
			Rect(0, Window::ClientHeight() * 0.5, Window::ClientWidth(), 10).draw(ColorF(1, 0, 0));
			for (int i = 0; i < 20; i++) {
				Rect(i * 100, Window::ClientHeight() * 0.5, 3, 100).draw(ColorF(1, 0, 0));
			}
			
		default:
			break;
	}
}

int DodgeGame::HitScopeCheck(int r1, Vec2 z1, int r2, Vec2 z2)
{	//スコープとどれだけ当たっているか（Hitlevel）
	float d;
	Vec2 gap(z2 - z1);
	d = sqrt((gap.x * gap.x) + (gap.y * gap.y));

	return (1-(d/(r1 + r2) ))*100;	//接している割合hitLevelに0％以上が返る

}

//引数用関数＊３
int DodgeGame::getBallCnt() {
	return ballCnt;
}

float DodgeGame::getDVelocity() {
	return dVelocity;
}

int DodgeGame::getHitLevel() {
	return hitLevel;
}

//センサの値とる（5未満は未判定）
bool DodgeGame::getHitSensorState() {
	dVelocity = abs(Sensor::getAcceleration().z);
	if (dVelocity >= 5)	return true;
	else return false;
}