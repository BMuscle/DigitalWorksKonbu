#include "TotalPlayTimeTimer.h"

Stopwatch TotalPlayTimeTimer::stopwatch;//�X�g�b�v�E�H�b�`

//�X�g�b�v�E�H�b�`���J�n�E�ĊJ����
void TotalPlayTimeTimer::start() {
	stopwatch.start();
}
//�X�g�b�v�E�H�b�`���J�n����
void TotalPlayTimeTimer::restart() {
	stopwatch.restart();
}
//�X�g�b�v�E�H�b�`���ꎞ��~����
void TotalPlayTimeTimer::pause() {
	stopwatch.pause();
}
//�b����64bit�����ŕԂ�
int64 TotalPlayTimeTimer::getSecond() {
	return stopwatch.s64();
}