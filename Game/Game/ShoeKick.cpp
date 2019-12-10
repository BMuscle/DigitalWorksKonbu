#include "ShoeKick.h"

ShoeKick::ShoeKick(void) {

}
ShoeKick::~ShoeKick(void) {

}
bool ShoeKick::isReady(void) {	//ロード終了してもいいかどうか

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

}
void ShoeKick::outputResult(void) {//結果をDBへ出力する

}