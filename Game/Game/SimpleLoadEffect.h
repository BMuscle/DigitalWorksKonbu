#pragma once
#include <Siv3D.hpp>

class SimpleLoadEffect {
private:
	enum class SIMPLE_LOAD_STATE {
		NONE,
		DARKING,
		DARK,
		DARK_WAIT,
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

	void nextState();//状態を次の状態へ移行する DARKから抜ける等

	//真っ暗の状態になっているかどうか
	bool isDark();
	//真っ暗から暗転明け待機(ロード完了待ち)
	bool isDarkWait();
	//明るくなっているかどうかTRUEの場合終了する
	bool isEnd();
	//現在がロード状態ならtrueを返す
	bool isLoad();
};