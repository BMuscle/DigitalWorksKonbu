#pragma once
#include <Siv3D.hpp>
#include <vector>

/*
	�ėp�I�i�p�x�������j���ʉ���֗��ɂǂ�����ł��Đ��ł���悤�ȃN���X
	Main�֐����̂ŏ������I���������s��
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