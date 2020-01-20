#pragma once
#include <Siv3D.hpp>
#include "ShoeKickGame.h"
#include "MyImageEffect.h"
#include "MyEffects.h"
class Shoe {
private:
	
	Array<bool> *hasItems;//�擾���Ă���A�C�e��

	bool isFly;			//���ł��邩�t���O
	bool isRotation;	//��]�t���O
	float angle;		//��]��
	float angleSpeed;	//��]�X�s�[�h
	Texture* texture;

	Vec2 shoeVecInit;	//�C��΂��x�N�g�������l
	Vec2 shoeVec;		//�C��΂��x�N�g��
	Vec2 totalShoeVec;	//���ړ�����
	float gravity;		//�d��

	MyEffects* effects;
	MyImageEffect* rocketEffect;
	MyImageEffect* angelEffect;

	int rocketCnt;
	int angelCnt;
	void updateRocket();
	void updateAngel();

	Vec2 getShoePos();

public:
	Shoe(Array<bool> *hasItems);
	~Shoe();
	void setAngle(bool rotate);
	bool update();
	void draw();

	Vec2 getTotalVec();

	void setShoeVector(float kickPower);

	void setGround();

	void setFly(bool fly);
	bool isFlying();
};