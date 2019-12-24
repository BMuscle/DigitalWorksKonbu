#pragma once
#include <Siv3D.hpp>
#include "MyImageEffect.h"
#include "EffectInterFace.h"
#include <list>

/*-----------------------------------------------
�N���X���FMyEffects
���@�@���F�G�t�F�N�g���ꊇ�Ǘ�����N���X
------------------------------------------------*/
class MyEffects {
private:
	struct EffectPack {
		EffectInterFace* effect;//�G�t�F�N�g
		Vec2 pos;				//�`����W
		float addTime;			//�ǉ����ꂽ����
	};
	std::list<EffectPack> effects;//�G�t�F�N�g�ꗗ
	Stopwatch stopwatch;//�X�g�b�v�E�H�b�`
public:
	//����������
	MyEffects();

	//�I������
	~MyEffects();

	//�G�t�F�N�g�ǉ��i���W�w��j
	void add(EffectInterFace* effect, Vec2 pos);

	//�S�̂�`�揈��
	void draw();

	//�ꎞ��~
	void pause();

	//�ĊJ
	void resume();

	//�ꎞ��~�m�F
	bool isPaused();

	//�ꊇ�폜
	void clear();

	//�G�t�F�N�g���󂩂ǂ���
	bool isEmpty();
};