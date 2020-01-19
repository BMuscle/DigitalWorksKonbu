#include "ShoeKickGame.h"

#define FPS 60

#define METER_WEIGHT 0.01

#define KICK_COUNT 3

//何メートル置きに表示するか
#define SIGNBOARD_INTERVAL 100

ShoeKickGame::ShoeKickGame(SHOEKICK_SCENE* scenep) : ShoeKickSceneBase(scenep) {
	//持っているアイテムを格納
	for (int i = 0; i < (int)GACHA_ITEM::SIZE; i++) {
		hasItems.push_back(User::getHasItems(GAME_TYPE::SHOEKICK, i + 1));
	}
	//画像のロード
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

	totalShoeVec = Vec2(0, GROUND - 80);
	gravity = 0.7;

	boardVec.push_back(createSignBoard(0));
	boardVec.push_back(createSignBoard(50));
	boardVec.push_back(createSignBoard(100));
	boardVec.push_back(createSignBoard(150));
	boardVec.push_back(createSignBoard(200));
	boardVec.push_back(createSignBoard(250));
	boardVec.push_back(createSignBoard(300));
	boardVec.push_back(createSignBoard(350));
	boardVec.push_back(createSignBoard(400));

	character = new ShoeCharacter(Vec2(0,GROUND));
	shoe = new Shoe();

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

	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/shoekick/game.wav");
	backAudio->setLoop(true);
	backAudio->play();

	//キックから始まるのでタイマーstart余白１秒
	setKickTimer(FPS * (KICK_COUNT + 1.5));
}

void ShoeKickGame::update(void) {
	if (isDescription) {//初回説明
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
		character->setVecMoveLeft(Window::ClientWidth() / 2 - totalShoeVec.x);
		break;
	case ShoeKickGame::END:
		frameCnt--;
		character->setVecMoveLeft(Window::ClientWidth() / 2 - totalShoeVec.x);
		if (frameCnt < 0) {
			setNextScene(SHOEKICK_SCENE::RESULT);
		}
		break;
	}

	character->update();
	shoe->update();
}

void ShoeKickGame::draw(void) {
	int x = Window::ClientWidth() / 2 - ((int)totalShoeVec.x % Window::ClientWidth());
	//背景描画
	TextureAsset(U"shoekick_game").drawAt(x, Window::ClientHeight() / 2);
	TextureAsset(U"shoekick_game").drawAt(x + Window::ClientWidth(), Window::ClientHeight() / 2);


	//METER描画
	int meter = (int)(totalShoeVec.x * METER_WEIGHT);
	Rect tmp = FontAsset(U"shoekick_font")(Format(meter) + U"M").boundingRect();			//座標系さん
	TextureAsset(U"shoekick_frame").draw(500 - 450, 100 + 0);	//フレーム描画
	FontAsset(U"shoekick_font")(Format(meter) + U"m").draw(500 - tmp.w,100,ColorF(0,0,0,1));//文字描画
	//看板描画
	for (auto vec : boardVec) {
		TextureAsset(U"shoekick_signboard").drawAt(vec.vec.x - totalShoeVec.x, vec.vec.y);
		FontAsset(U"shoekick_boardfont")(Format(vec.meter)).drawAt(vec.vec.x - totalShoeVec.x, vec.vec.y, ColorF(0, 0, 0));
	}
	//Character描画
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

	if (isDescription) {//初回説明描画
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
	constexpr int KICKINTERVAL = FPS * 1;//蹴るを受け付ける時間
	updateKickTimer();
	if (kickCount > 0) {//カウントダウン中
		if (kickCount % FPS == 0) {
			//効果音鳴らす

		}
	}
	else if (kickCount == -54) {
	//else if (kickCount == -34) {
		character->setMoveJump();
	}
	else if (kickCount > -KICKINTERVAL) {//カウントダウンが終了したのでキック時間
		Vec3 acc = Sensor::getAcceleration();
	
		//瞬間加速度最大値を取得
		if (kickPower < abs(acc.x)) {
			kickPower = abs(acc.x);
		}
	}
	else {//キック時間下限
		setNextState(FLY);//シーン移行する
		if (kickPower <= 0) {
			kickPower = 20.0;
		}
		shoeVec = Vec2(kickPower / 2, -(kickPower / 4.0));//靴飛ばしのパワーを求める。
	}
}

void ShoeKickGame::drawKick() {
	if (isStart) {
		drawKickTimer();
	}
}

void ShoeKickGame::updateFly() {
	if (totalShoeVec.y >= GROUND) {//もし地面に着いているならば
		shoe->setAngle(false);//回転停止
		totalShoeVec.y = GROUND;//座標を地面に修正
		if (shoeVec.x > 0) {//少し右に惰性で動かす
			shoeVec.x -= 5;
			totalShoeVec.x += shoeVec.x;
		}
		else {
			shoeVec.x = 0;
			setNextState(GAME_STATE::END);
			frameCnt = 100;
		}
	}
	else {//飛んでいる最中
		shoe->setAngle(true);//回転開始
		totalShoeVec += shoeVec;//座標移動
		shoeVec.y += gravity / 2.0;
		if (shoeVec.y < 0) {//上昇中
			shoeVec.x -= 0.1;
		}
		else {//下降中
			shoeVec.x += 0.1;
		}
	}
}

void ShoeKickGame::drawFly() {
	//靴描画
	shoe->draw(Vec2(Window::ClientWidth() / 2, totalShoeVec.y));
}

//蹴る時のカウントダウン
void ShoeKickGame::updateKickTimer() {
	kickCount--;
}

//蹴る時のカウントダウン描画
void ShoeKickGame::drawKickTimer() {
	int cnt = kickCount / FPS + 1;
	if (cnt > 3) {
		return;
	}
	if (kickCount > 0) {
		//数字描画
		countTexture[cnt]->drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
	}
	else {
		//蹴れ！を描画
		countTexture[0]->drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
	}
}

//蹴る時のカウントダウンセット
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
	return totalShoeVec.x * METER_WEIGHT;
}