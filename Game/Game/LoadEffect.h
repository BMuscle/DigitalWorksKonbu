#pragma once
#include <Siv3D.hpp>

enum class LOAD_STATE//現在のロードの状態をあらわす
{
	NONE,//ロード中ではない
	DARKING,//暗くなり始める
	DARK,//暗くなった
	BLACK,//真っ黒の画面
	BRIGHTING,//明るくなり始める
	BRIGHT,//明るくなった
	END,//終了
};

class LoadEffect {
private:
	LOAD_STATE loadState;
	float alpha;
public:
	LoadEffect();
	~LoadEffect();
	void loadStart();
	void nextState();//ロード状態を次の状態へ進める
	void update();
	void draw();

	LOAD_STATE getLoadState();//現在のロード状態を返す
};