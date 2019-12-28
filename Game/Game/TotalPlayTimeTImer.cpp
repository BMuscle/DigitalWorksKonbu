#include "TotalPlayTimeTimer.h"

Stopwatch TotalPlayTimeTimer::stopwatch;//ストップウォッチ

//ストップウォッチを開始・再開する
void TotalPlayTimeTimer::start() {
	stopwatch.start();
}
//ストップウォッチを開始する
void TotalPlayTimeTimer::restart() {
	stopwatch.restart();
}
//ストップウォッチを一時停止する
void TotalPlayTimeTimer::pause() {
	stopwatch.pause();
}
//秒数を64bit整数で返す
int64 TotalPlayTimeTimer::getSecond() {
	return stopwatch.s64();
}