#pragma once
#include <Siv3D.hpp>

//画像と画像の中央に文字を描画するクラス
class MyImageButton {
public:
	//フォルダパス(中にon.png off.png)、画像中央の文字
	MyImageButton(String path, String word, int fontsize, int x, int y, bool initselect = false);
	~MyImageButton();
	//ロードが完了しているかどうか
	bool isReady();
	//アルファ値をセットする
	void setAlpha(float alpha);
	//文字とセットで描画
	void draw(ColorF color = ColorF(0,0,0));
	//文字なしで描画する
	void drawNotWord( bool selected = false);
	//セレクトされているか状態をセットする
	void setSelect(bool flag);
	//セレクト状態を返す
	bool isSelect();
private:
	String folderpath;			//画像on off が格納されているフォルダパス
	Font font;					//フォント
	String drawWord;			//描画する文字
	bool selected;				//セレクト状態
	int buttonX, buttonY;		//描画座標
	float buttonAlpha;			//アルファ値
};