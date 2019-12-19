#pragma once
#include <Siv3D.hpp>

//�摜�Ɖ摜�̒����ɕ�����`�悷��N���X
class MyImageButton {
public:
	//�t�H���_�p�X(����on.png off.png)�A�摜�����̕���
	MyImageButton(String path, String word, int fontsize, int x, int y, bool initselect = false);
	~MyImageButton();
	//���[�h���������Ă��邩�ǂ���
	bool isReady();
	//�A���t�@�l���Z�b�g����
	void setAlpha(float alpha);
	//�����ƃZ�b�g�ŕ`��
	void draw(ColorF color = ColorF(0,0,0));
	//�����Ȃ��ŕ`�悷��
	void drawNotWord( bool selected = false);
	//�Z���N�g����Ă��邩��Ԃ��Z�b�g����
	void setSelect(bool flag);
	//�Z���N�g��Ԃ�Ԃ�
	bool isSelect();
private:
	String folderpath;			//�摜on off ���i�[����Ă���t�H���_�p�X
	Font font;					//�t�H���g
	String drawWord;			//�`�悷�镶��
	bool selected;				//�Z���N�g���
	int buttonX, buttonY;		//�`����W
	float buttonAlpha;			//�A���t�@�l
};