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
	//初期化
	static void initialize(bool debugMode = false);	
	//終了化
	static void finalize();		
	//デバッグモード時の計算処理
	static void update();		
	//デバッグ用の出力（簡易文字、図形）を行う
	static void debugPrint();
	//加速度を返す(Vec3)
	static Vec3 getAcceleration();
	//角速度を返す(Vec3)
	static Vec3 getAngularvelocity();
	//方向を返す(Vec3)
	static Vec3 getDirection();
	//センサーデータの格納
	static void setData(Vec3& accel, Vec3& angular, Vec3& dir);
};