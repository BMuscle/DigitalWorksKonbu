#include "Soccer.h"

Soccer::Soccer(void) {

}
Soccer::~Soccer(void) {

}
bool Soccer::isReady(void) {	//ロード終了してもいいかどうか

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

}
void Soccer::outputResult(void) {//結果をDBへ出力する

}