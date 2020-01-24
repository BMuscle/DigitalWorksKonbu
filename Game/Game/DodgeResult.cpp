#include"DodgeResult.h"


DodgeResult::DodgeResult(DODGE_SCENE* nextScene) :DodgeSceneBase(nextScene) {
	TextureAsset::Register(U"dodgeresult", U"resources/images/backs/game/dodge/result.png");

	mainFont(70, U"resources/font/kokuban.ttf");
	subFont = Font(80, U"resources/font/kokuban.ttf");


	//20 と 1800がボタンのX座標
	button[MAP]   = new MyImageButton(U"resources/images/items/game/dodge/map", U"", 0, 20, Window::ClientHeight() * 0.5);
	button[TITLE] = new MyImageButton(U"resources/images/items/game/dodge/title", U"", 0, 1800, Window::ClientHeight() * 0.5);

	//値テスト用初期化
	for (int i = 0; i < DODGE_GAME_PLAY_COUNT; i++) {
		dVelocity[i] = 10;
		hitLevel[i] = 50;
		hit[i] = true;
	}
}
DodgeResult::~DodgeResult() {
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;

	delete button[TITLE];
	delete button[MAP];
}

void DodgeResult::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}

void DodgeResult::update() {
	if (MyKey::getRightKeyDown()) {//右キー入力
		nowselect = MAP;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
	else if (MyKey::getLeftKeyDown()) {//左キー入力
		nowselect =TITLE;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
	else if (MyKey::getDecisionKey()) {
		switch (nowselect)
		{
		case DodgeResult::MAP:
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		case DodgeResult::TITLE:
			setNextScene(DODGE_SCENE::TITLE);
			break;
		default:
			break;
		}
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}
}

void DodgeResult::draw() {
	constexpr int basePosY[DODGE_GAME_PLAY_COUNT]{
		495,
		620,
		740
	};
	constexpr int basePosX[DODGE_GAME_PLAY_COUNT]{
		660,
		910,
		1206,
	};
	//背景描画
	TextureAsset(U"dodgeresult").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	//文字描画
	for (int i = 0; i < DODGE_GAME_PLAY_COUNT; i++) {
		if (hit[i]) { subFont(U"〇").drawAt(basePosX[0], basePosY[i], Color(255,204,255)); }
		else { subFont(U"×").drawAt(basePosX[0], basePosY[i], Color(153, 255,255)); }
		subFont(Format(dVelocity[i])).drawAt(basePosX[1], basePosY[i]);
		subFont(Format(hitLevel[i]) + U"%").drawAt(basePosX[2], basePosY[i]);
	}
	//ボタン描画
	switch (nowselect)
	{
	case DodgeResult::MAP:
		button[TITLE]->drawNotWord(false);
		button[MAP]->drawNotWord(true);
		break;
	case DodgeResult::TITLE:
		button[TITLE]->drawNotWord(true);
		button[MAP]->drawNotWord(false);
		break;
	}
	

}
