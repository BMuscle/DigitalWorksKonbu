#pragma once
#include <Siv3D.hpp>
#include <vector>
#include "EffectInterFace.h"

/*-----------------------------------------------------------------------------------
	クラス名:MyImageEffect
	機　  能:連番画像のエフェクトを扱う
	説　　明:エフェクトクラスにaddして使用する
-------------------------------------------------------------------------------------*/
class MyImageEffect : public EffectInterFace {
private:
	float switchingTime;	//画像を切り替える時間
	int frameNumber;		//画像の枚数
	int rotate;
	std::vector<TextureRegion> animationTexture;//アニメーション用テクスチャ画像（切り分けされた後)
public:
	MyImageEffect(String filepath, const int frameX, const int frameY, const float switchingTime = 0.03, int rotate = 0);
	~MyImageEffect();
	bool update(float t, const Vec2& pos) override;//オーバライド　計算処理　描画処理も兼ねている
};
