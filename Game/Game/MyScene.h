#pragma once

//�p���p Scene�C���^�[�t�F�[�X
class MyScene {
public:
	MyScene(void) {}
	virtual ~MyScene(void) {}
	virtual bool isReady(void) = 0;	//���[�h�I�����Ă��������ǂ���
	virtual void start(void) = 0;	//���[�h�󂯂���Ɏ��s��������
	virtual void update(void) = 0;	//�v�Z����
	virtual void draw(void) = 0;	//�`�揈��
};