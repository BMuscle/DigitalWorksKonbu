#pragma once

//継承用 Sceneインターフェース
class MyScene {
public:
	MyScene(void) {}
	virtual ~MyScene(void) {}
	virtual bool isReady(void) = 0;	//ロード終了してもいいかどうか
	virtual void start(void) = 0;	//ロード空けた後に実行されるもの
	virtual void update(void) = 0;	//計算処理
	virtual void draw(void) = 0;	//描画処理
};