#pragma once
#include <Siv3D.hpp>
#include "ShoeKickGame.h"

class ShoeCharacter {
private:
	Vec2 pos;						//���W
	Array<Texture*> textureArray;	//�A�ԉ摜
	int textureIndex;				//�摜�����ڂ�
	const Vec2 moveSpeed;			//�ړ��X�s�[�h
	Vec2 jumpSpeed;					//�W�����v����X�s�[�h
	bool isJump;					//�W�����v���Ă��邩�t���O
	bool isMove;					//�ړ����Ă��邩�t���O

	int moveCnt;					//����ړ�������A�ړ����邩�ǂ���

	void moveRight();				//�E�ړ�
	void moveJump();				//�W�����v����
public:
	ShoeCharacter(Vec2 init);
	~ShoeCharacter();
	//�v�Z����
	void update();
	//�E�ړ��t���OON
	void setMoveRight();
	//���փx�N�g���ʈړ�������
	void setVecMoveLeft(int x);
	//�W�����v�t���OON
	void setMoveJump();
	//�`�揈��
	void draw();

	Vec2 getPos();
};