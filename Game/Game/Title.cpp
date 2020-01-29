#include "Title.h"

Title::Title(void) {
	FontAsset::Register(U"titlefont", 80);
	FontAsset::Preload(U"titlefont");
	TextureAsset::Register(U"titleback", U"resources/images/backs/title.png", AssetParameter::LoadAsync());
	AudioAsset::Register(U"titledecision", U"resources/musics/items/title/decision.wav");
}

Title::~Title(void) {
	FontAsset::Unregister(U"titlefont");
	TextureAsset::Unregister(U"titleback");

	delete backAudio;
}

bool Title::isReady(void) {
	if (TextureAsset::IsReady(U"titleback")) {
		return true;
	}
	return false;
}

void Title::start(void) {
	delete backAudio;
	backAudio = new Audio(U"resources/musics/backs/title.wav");
	backAudio->setLoop(true);
	backAudio->setVolume(0.1);
	backAudio->play();
}


void Title::update(void) {
	if (MyKey::getDecisionKey()) {//決定キーで次のシーンへ移行
		MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);
		AudioAsset(U"titledecision").setVolume(0.3);
		AudioAsset(U"titledecision").play();
	}
	else {
		changeAlpha();
	}
}

void Title::draw(void) {
	//背景の描画
	TextureAsset(U"titleback").draw();
	//タイトルのフォント
	FontAsset(U"titlefont")(U"～ Play ～").drawAt(Scene::Width() *0.27, Scene::Height() - 200 + 3, ColorF(0, 0, 0, alpha - 0.05));
	FontAsset(U"titlefont")(U"～ Play ～").drawAt(Scene::Width() * 0.27, Scene::Height() - 200, AlphaF(alpha));
}

void Title::changeAlpha(void) {
	constexpr int CYCLE = 3000;//透過が変わる周期
	const uint64 t = Time::GetMillisec();
	alpha = Sin(t % CYCLE / static_cast<double>(CYCLE)* s3d::Math::Constants::TwoPi) * 0.42 + 0.58;
}