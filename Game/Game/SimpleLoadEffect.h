#pragma once
#include <Siv3D.hpp>



class SimpleLoadEffect {
private:
	enum class SIMPLE_LOAD_STATE {
		NONE,
		DARKING,
		DARK,
		BRIGHTING,
		END,
	};

	SIMPLE_LOAD_STATE loadState;
	float loadSecond;//ロード時間秒数
	Stopwatch stopwatch;
	float alpha;//アルファ値
public:

	SimpleLoadEffect();
	~SimpleLoadEffect();

	//ロードを開始させる secondはトータルのロード時間
	void start(float second = 1);
	//計算処理
	void update();
	//描画処理
	void draw();

	//真っ暗の状態になっているかどうかTRUEの場合その次フレームから明るくなり始める。
	bool isDark();
	//明るくなっているかどうかTRUEの場合終了する
	bool isEnd();
	//現在がロード状態ならtrueを返す
	bool isLoad();
};