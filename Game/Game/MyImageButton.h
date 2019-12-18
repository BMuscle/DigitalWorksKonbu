#pragma once
#include <Siv3D.hpp>

//�摜�Ɖ摜�̒����ɕ�����`�悷��N���X
class MyImageButton {
public:
	//�t�H���_�p�X(����on.png off.png)�A�摜�����̕���
	MyImageButton(String path, String word, int fontsize, int x, int y, bool initselect = false);
	~MyImageButton();
	bool isReady();
	void setAlpha(float alpha);
	void draw(ColorF color = ColorF(0,0,0));
	void drawNotWord( bool selected = false);
	void setSelect(bool flag);//�Z���N�g����Ă��邩��Ԃ��Z�b�g����
	bool isSelect();//�Z���N�g��Ԃ�Ԃ�
private:
	String folderpath;
	Font font;//�t�H���g
	String drawWord;//�`�悷�镶��
	bool selected;//�Z���N�g���
	int buttonX, buttonY;//�`����W
	float buttonAlpha;//�A���t�@�l
};