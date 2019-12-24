#pragma once
#include <Siv3D.hpp>



class SimpleLoadEffect {
private:
	enum class SIMPLE_LOAD_STATE {
		NONE,
		DARKING,
		DARK,
		BRIGHTING,
		END,
	};

	SIMPLE_LOAD_STATE loadState;
	float loadSecond;//���[�h���ԕb��
	Stopwatch stopwatch;
	float alpha;//�A���t�@�l
public:

	SimpleLoadEffect();
	~SimpleLoadEffect();

	//���[�h���J�n������ second�̓g�[�^���̃��[�h����
	void start(float second = 1);
	//�v�Z����
	void update();
	//�`�揈��
	void draw();

	//�^���Â̏�ԂɂȂ��Ă��邩�ǂ���TRUE�̏ꍇ���̎��t���[�����疾�邭�Ȃ�n�߂�B
	bool isDark();
	//���邭�Ȃ��Ă��邩�ǂ���TRUE�̏ꍇ�I������
	bool isEnd();
	//���݂����[�h��ԂȂ�true��Ԃ�
	bool isLoad();
};