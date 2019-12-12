#include "Dodge.h"

Dodge::Dodge(void) {
	//アセットへロード
	FontAsset::Register(U"dodgefont", 70);
	FontAsset::Preload(U"dodgefont");
	TextureAsset::Register(U"dodgeback", U"resources/images/backs/dodge.png", AssetParameter::LoadAsync());
}
Dodge::~Dodge(void) {
	FontAsset::Unregister(U"dodgefont");
	TextureAsset::Unregister(U"dodgeback");
	delete backAudio;
}
bool Dodge::isReady(void) {	//ロード終了してもいいかどうか
	if (TextureAsset::IsReady(U"dodgeback")) {
		return true;
	}
	return false;
}
void Dodge::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/dodge.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void Dodge::update(void) {	//計算処理

}
void Dodge::draw(void) {	//描画処理
	TextureAsset(U"dodgeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}
void Dodge::outputResult(void) {//結果をDBへ出力する

}