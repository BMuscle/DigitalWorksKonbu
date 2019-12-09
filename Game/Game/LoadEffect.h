#pragma once
#include <Siv3D.hpp>

enum class LOAD_STATE//���݂̃��[�h�̏�Ԃ�����킷
{
	NONE,//���[�h���ł͂Ȃ�
	DARKING,//�Â��Ȃ�n�߂�
	DARK,//�Â��Ȃ���
	BLACK,//�^�����̉��
	BRIGHTING,//���邭�Ȃ�n�߂�
	BRIGHT,//���邭�Ȃ���
	END,//�I��
};

class LoadEffect {
private:
	LOAD_STATE loadState;
	float alpha;
public:
	LoadEffect();
	~LoadEffect();
	void loadStart();
	void nextState();//���[�h��Ԃ����̏�Ԃ֐i�߂�
	void update();
	void draw();

	LOAD_STATE getLoadState();//���݂̃��[�h��Ԃ�Ԃ�
};