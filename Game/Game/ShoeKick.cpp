#include "ShoeKick.h"

ShoeKick::ShoeKick(void) {
	//アセットへロード
	FontAsset::Register(U"shoekickfont", 70);
	FontAsset::Preload(U"shoekickfont");
	TextureAsset::Register(U"shoekickback", U"resources/images/backs/shoekick.png", AssetParameter::LoadAsync());
}
ShoeKick::~ShoeKick(void) {
	FontAsset::Unregister(U"shoekickfont");
	TextureAsset::Unregister(U"shoekickback");
	delete backAudio;
}
bool ShoeKick::isReady(void) {	//ロード終了してもいいかどうか
	if (TextureAsset::IsReady(U"shoekickback")) {
		return true;
	}
	return false;
}
void ShoeKick::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/shoekick.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void ShoeKick::update(void) {	//計算処理

}
void ShoeKick::draw(void) {	//描画処理
	TextureAsset(U"shoekickback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}
void ShoeKick::outputResult(void) {//結果をDBへ出力する

}