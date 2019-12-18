#pragma once
#include <Siv3D.hpp>

//画像と画像の中央に文字を描画するクラス
class MyImageButton {
public:
	//フォルダパス(中にon.png off.png)、画像中央の文字
	MyImageButton(String path, String word, int fontsize, int x, int y, bool initselect = false);
	~MyImageButton();
	bool isReady();
	void setAlpha(float alpha);
	void draw(ColorF color = ColorF(0,0,0));
	void drawNotWord( bool selected = false);
	void setSelect(bool flag);//セレクトされているか状態をセットする
	bool isSelect();//セレクト状態を返す
private:
	String folderpath;
	Font font;//フォント
	String drawWord;//描画する文字
	bool selected;//セレクト状態
	int buttonX, buttonY;//描画座標
	float buttonAlpha;//アルファ値
};