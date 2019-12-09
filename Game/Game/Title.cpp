#include "Title.h"

Title::Title(void) {
	FontAsset::Register(U"titlefont", 70);
	FontAsset::Preload(U"titlefont");
	TextureAsset::Register(U"titleback", U"resources/images/back/title.jpg", AssetParameter::LoadAsync());
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
	backAudio = new Audio(U"resources/musics/");
	backAudio->setLoop(true);
	backAudio->play();
}


void Title::update(void) {
	if (MyKey::getDecisionKey()) {
		MySceneManager::setNextScene(SCENE::SYNCRC);
	}
	else {
		changeAlpha();
	}
}

void Title::draw(void) {

	TextureAsset(U"titleback").draw();
	
	int a = Window::ClientWidth() / 2;
	int b = Window::ClientWidth();

	FontAsset(U"titlefont")(U"`Press Button To Start`").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 150 + 3, ColorF(0, 0, 0, alpha - 0.05));
	FontAsset(U"titlefont")(U"`Press Button To Start`").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 150, AlphaF(alpha));
}

void Title::changeAlpha(void) {
	constexpr int CYCLE = 3000;//“§‰ß‚ª•Ï‚í‚éüŠú
	const uint64 t = Time::GetMillisec();
	alpha = Sin(t % CYCLE / static_cast<double>(CYCLE)* s3d::Math::Constants::TwoPi) * 0.42 + 0.58;
}