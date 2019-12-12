#include "Soccer.h"

Soccer::Soccer(void) {
	//アセットへロード
	FontAsset::Register(U"soccerfont", 70);
	FontAsset::Preload(U"soccerfont");
	TextureAsset::Register(U"soccerback", U"resources/images/backs/soccer.png", AssetParameter::LoadAsync());
}
Soccer::~Soccer(void) {
	FontAsset::Unregister(U"soccerfont");
	TextureAsset::Unregister(U"soccerback");
	delete backAudio;
}
bool Soccer::isReady(void) {	//ロード終了してもいいかどうか
	if (TextureAsset::IsReady(U"soccerback")) {
		return true;
	}
	return false;
}
void Soccer::start(void){	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/soccer.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void Soccer::update(void) {	//計算処理

}
void Soccer::draw(void) {	//描画処理
	TextureAsset(U"soccerback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}
void Soccer::outputResult(void) {//結果をDBへ出力する

}