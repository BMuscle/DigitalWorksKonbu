#include "Dodge.h"

Dodge::Dodge(void) {

}
Dodge::~Dodge(void) {

}
bool Dodge::isReady(void) {	//ロード終了してもいいかどうか

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

}
void Dodge::outputResult(void) {//結果をDBへ出力する

}