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
	TextureAsset::Register(U"shoekick_game", U"resources/images/backs/game/shoekick/game.png");
	TextureAsset::Register(U"shoekick_frame", U"resources/images/items/game/shoekick/game/frame.png");
	TextureAsset::Register(U"shoekick_signboard", U"resources/images/items/game/shoekick/game/signboard.png");
	TextureAsset::Register(U"shoekick_description", U"resources/images/items/game/shoekick/game/description.png");

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



	boardVec.push_back(createSignBoard(0));
	boardVec.push_back(createSignBoard(50));
	boardVec.push_back(createSignBoard(100));
	boardVec.push_back(createSignBoard(150));
	boardVec.push_back(createSignBoard(200));
	boardVec.push_back(createSignBoard(250));
	boardVec.push_back(createSignBoard(300));
	boardVec.push_back(createSignBoard(350));
	boardVec.push_back(createSignBoard(400));
	boardVec.push_back(createSignBoard(450));
	boardVec.push_back(createSignBoard(500));
	boardVec.push_back(createSignBoard(550));
	boardVec.push_back(createSignBoard(600));
	boardVec.push_back(createSignBoard(650));
	boardVec.push_back(createSignBoard(700));

	character = new ShoeCharacter(Vec2(0,GROUND));
	shoe = new Shoe(&hasItems);

	frameCnt = 0;

	isDescription = true;


	AudioAsset::Register(U"whistle", U"resources/musics/items/game/shoekick/whistle.wav");
	AudioAsset::Register(U"drum", U"resources/musics/items/game/shoekick/drum.wav");

}
ShoeKickGame::~ShoeKickGame() {
	delete backAudio;

	TextureAsset::Unregister(U"shoekick_game");
	TextureAsset::Unregister(U"shoekick_frame");
	TextureAsset::Unregister(U"shoekick_signboard");
	TextureAsset::Unregister(U"shoekick_description");

	FontAsset::Unregister(U"shoekick_font");
	FontAsset::Unregister(U"shoekick_boardfont");

	AudioAsset::Unregister(U"whistle");
	AudioAsset::Unregister(U"drum");

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
	backAudio = new Audio(U"resources/musics/backs/shoekick/game.mp3");
	backAudio->setVolume(0.05);
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
		character->setVecMoveLeft(Scene::Width() / 2 - shoe->getTotalVec().x);
		break;
	case ShoeKickGame::END:
		frameCnt--;
		character->setVecMoveLeft(Scene::Width() / 2 - shoe->getTotalVec().x);
		if (frameCnt < 0) {
			setNextScene(SHOEKICK_SCENE::RESULT);
		}
		break;
	}

	character->update();

}

void ShoeKickGame::draw(void) {
	float subY = shoe->getTotalVec().y - GROUND + 80;
	if (subY > 0) {
		subY = 0;
	}
	else if (subY < -Scene::Height() * 3) {
		subY = -Scene::Height() * 3;
	}

	int x = Scene::Width() / 2 - ((int)shoe->getTotalVec().x % Scene::Width());
	//背景描画
	TextureAsset(U"shoekick_game").drawAt(x, -Scene::Height() / 2 - (subY));
	TextureAsset(U"shoekick_game").drawAt(x + Scene::Width(), -Scene::Height() / 2 - (subY));


	//METER描画
	int meter = (int)(shoe->getTotalVec().x * METER_WEIGHT);
	Rect tmp = FontAsset(U"shoekick_font")(Format(meter) + U"M").boundingRect();			//座標系さん
	TextureAsset(U"shoekick_frame").draw(500 - 450, 100 + 0);	//フレーム描画
	FontAsset(U"shoekick_font")(Format(meter) + U"m").draw(500 - tmp.w,100,ColorF(0,0,0,1));//文字描画
	//看板描画
	for (auto vec : boardVec) {
		TextureAsset(U"shoekick_signboard").drawAt(vec.vec.x - shoe->getTotalVec().x, vec.vec.y - (subY));
		FontAsset(U"shoekick_boardfont")(Format(vec.meter)).drawAt(vec.vec.x - shoe->getTotalVec().x, vec.vec.y - (subY), ColorF(0, 0, 0));
	}
	//Character描画
	character->draw(subY);


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
	//初回説明描画
	if (isDescription) {
		Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(1, 1, 1, 0.8));
		TextureAsset(U"shoekick_description").drawAt(Scene::Center());
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
		character->setMoveJump();
	}
	else if (kickCount > -KICKINTERVAL) {//カウントダウンが終了したのでキック時間
		Vec3 acc = Sensor::getAcceleration();
	
		//瞬間加速度最大値を取得
		if (kickPower < abs(acc.z)) {
			kickPower = abs(acc.z);
		}
	}
	else {//キック時間下限
		setNextState(FLY);//シーン移行する
		shoe->setFly(true);
		if (kickPower <= 0) {
			kickPower = 2;
		}
		shoe->setShoeVector(kickPower);//靴飛ばしのパワーを求める。
	}
}

void ShoeKickGame::drawKick() {
	if (isStart) {
		drawKickTimer();
	}
}

void ShoeKickGame::updateFly() {
	if (!shoe->update()) {
		setNextState(GAME_STATE::END);
		frameCnt = 100;
	}
}

void ShoeKickGame::drawFly() {
	//靴描画
	shoe->draw();
}

//蹴る時のカウントダウン
void ShoeKickGame::updateKickTimer() {
	if (kickCount == FPS * 3 ||
		kickCount == FPS * 2 ||
		kickCount == FPS * 1) {
		AudioAsset(U"drum").setVolume(0.3);
		AudioAsset(U"drum").setPosSec(0);
		AudioAsset(U"drum").play();
	}
	else if(kickCount == 0){
		AudioAsset(U"whistle").setVolume(0.3);
		AudioAsset(U"whistle").setPosSec(0);
		AudioAsset(U"whistle").play();
	}
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
		countTexture[cnt]->drawAt(Scene::Width() / 2, Scene::Height() * 0.4);
	}
	else {
		//蹴れ！を描画
		countTexture[0]->drawAt(Scene::Width() / 2, Scene::Height() * 0.4);
	}
}

//蹴る時のカウントダウンセット
void ShoeKickGame::setKickTimer(int kicktime) {
	kickCount = kicktime;
}

ShoeKickGame::SignBoard ShoeKickGame::createSignBoard(int meter) {
	SignBoard board;
	if (meter == 0) {
		board.vec = Vec2(Scene::Width() /2, GROUND - 120);
	}
	else {
		board.vec = Vec2(Scene::Width() / 2 + meter / METER_WEIGHT , GROUND - 120);
	}
	board.meter = meter;
	return board;
}

int ShoeKickGame::getMeter() {
	return shoe->getTotalVec().x * METER_WEIGHT;
}