#pragma once
#include <Siv3D.hpp>
#include <vector>

/*
	汎用的（頻度が高い）効果音を便利にどこからでも再生できるようなクラス
	Main関数内ので初期化終了処理を行う
*/

enum class SE_NAME {
	DECISION,
	CURSOR,
	SIZE,
};

class GeneralSoundEffects {
private:
	static std::vector<Audio*> audios;

public:
	GeneralSoundEffects() = delete;
	static void initialize();
	static void finalize();
	static void play(SE_NAME se_name);
};