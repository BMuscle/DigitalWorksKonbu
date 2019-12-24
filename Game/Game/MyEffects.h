#pragma once
#include <Siv3D.hpp>
#include "MyImageEffect.h"
#include "EffectInterFace.h"
#include <list>

/*-----------------------------------------------
クラス名：MyEffects
説　　明：エフェクトを一括管理するクラス
------------------------------------------------*/
class MyEffects {
private:
	struct EffectPack {
		EffectInterFace* effect;//エフェクト
		Vec2 pos;				//描画座標
		float addTime;			//追加された時間
	};
	std::list<EffectPack> effects;//エフェクト一覧
	Stopwatch stopwatch;//ストップウォッチ
public:
	//初期化処理
	MyEffects();

	//終了処理
	~MyEffects();

	//エフェクト追加（座標指定）
	void add(EffectInterFace* effect, Vec2 pos);

	//全体を描画処理
	void draw();

	//一時停止
	void pause();

	//再開
	void resume();

	//一時停止確認
	bool isPaused();

	//一括削除
	void clear();

	//エフェクトが空かどうか
	bool isEmpty();
};