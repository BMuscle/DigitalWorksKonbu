#pragma once
#include <Siv3D.hpp>
#include "MyKey.h"
class Sensor {
private:
	//加速度、角速度、方向
	static Vec3 acceleration, angularvelocity, direction;
	static bool debugMode;//デバッグモードを許可するかどうか、キー入力で値を入力できるようになる。(角速度未対応)
public:
	Sensor() = delete;
	static void initialize(bool debugMode = false);	//初期化
	static void finalize();		//終了化
	static void update();		//デバッグモード時の計算処理
	static Vec3 getAcceleration();//加速度を返す
	static Vec3 getAngularvelocity();//角速度を返す
	static Vec3 getDirection();//方向を返す
};