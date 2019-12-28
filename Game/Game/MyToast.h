#pragma once
#include "EffectInterFace.h"
#include <Siv3D.hpp>

/*-----------------------------------------------------------------------------------
	クラス名:MyToast
	機　  能:フラッシュメッセージのエフェクトを扱う
	説　　明:エフェクトクラスにaddして使用する
	※軽量化のためにフォントは統一している。登録すればするほど増えるので注意
-------------------------------------------------------------------------------------*/
class MyToast : public EffectInterFace {
private:
	String message;
	int fontSize;
	ColorF colorF;
	float endSecondF;	//メッセージ表示時間
	float flushSecondF;	//メッセージが明るくなる、暗くなる時の時間

public:
	MyToast(String message, const int fontSize = 70, ColorF colorF = ColorF(0,0,0), const float endSecondF = 1.0, const float flushSecondF = 0.5);
	~MyToast();
	bool update(float t, const Vec2& pos) override;//オーバライド　計算処理　描画処理も兼ねている
	void setMessage(String message);
};
