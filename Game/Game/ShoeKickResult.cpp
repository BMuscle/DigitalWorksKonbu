#include "ShoeKickResult.h"

#define SCORE_WEIGHT 200.0 //最高METER
#define POINT_WEIGHT 1.6

ShoeKickResult::ShoeKickResult(SHOEKICK_SCENE* scenep, int meter) : ShoeKickSceneBase(scenep) {
	TextureAsset::Register(U"shoekick_back", U"resources/images/backs/game/shoekick/result.png");
	TextureAsset::Register(U"shoekick_high", U"resources/images/items/game/shoekick/high.png");

	FontAsset::Register(U"shoekick_font", 70);
	FontAsset::Preload(U"shoekick_font");

	FontAsset::Register(U"shoekick_font_bold", 100, Typeface::Bold);
	FontAsset::Preload(U"shoekick_font_bold");

	FontAsset::Register(U"shoekick_font_small", 55);
	FontAsset::Preload(U"shoekick_font_small");
	this->meter = meter;

	int highScore = User::getGameHighScore(GAME_TYPE::SHOEKICK);
	//ユーザースコア保存
	int score = meter / SCORE_WEIGHT * 100.0;
	User::addGameScore(GAME_TYPE::SHOEKICK, score);

	int newScore = User::getGameHighScore(GAME_TYPE::SHOEKICK);
	if (highScore < newScore) {
		isHighScoreUpdate = true;
	}
	else {
		isHighScoreUpdate = false;
	}

	point = meter * POINT_WEIGHT;
	User::addUserPoint(point);
	alpha = 0;
	
}
ShoeKickResult::~ShoeKickResult() {
	delete backAudio;
	TextureAsset::Unregister(U"shoekick_back");
	TextureAsset::Unregister(U"shoekick_high");
	FontAsset::Unregister(U"shoekick_font");
	FontAsset::Unregister(U"shoekick_font_bold");
	FontAsset::Unregister(U"shoekick_font_small");
}

bool ShoeKickResult::isReady(void) {
	return true;
}
void ShoeKickResult::start(void) {
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/shoekick/result.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void ShoeKickResult::update(void) {
	changeAlpha();
	if (MyKey::getDecisionKey()) {
		setNextScene(SHOEKICK_SCENE::TITLE);
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}
}
void ShoeKickResult::draw(void) {
	//背景描画
	TextureAsset(U"shoekick_back").drawAt(Window::ClientCenter());
	FontAsset(U"shoekick_font_bold")(Format(meter) + U"m").drawAt(Window::ClientWidth() * 0.55, Window::ClientHeight() * 0.45, ColorF(0, 0, 0));
	FontAsset(U"shoekick_font_small")(Format(point) + U"P").drawAt(Window::ClientWidth() * 0.55, Window::ClientHeight() * 0.6, ColorF(0, 0, 0));
	if (isHighScoreUpdate) {//ハイスコア更新しているならば
		TextureAsset(U"shoekick_high").drawAt(Window::ClientWidth() * 0.5, Window::ClientHeight() * 0.72);
	}
	FontAsset(U"shoekick_font")(U"～Press to Enter～").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 160, ColorF(0, 0, 0, alpha));
}

void ShoeKickResult::changeAlpha(void) {
	constexpr int CYCLE = 3000;//透過が変わる周期
	const uint64 t = Time::GetMillisec();
	alpha = Sin(t % CYCLE / static_cast<double>(CYCLE)* s3d::Math::Constants::TwoPi) * 0.42 + 0.58;
}