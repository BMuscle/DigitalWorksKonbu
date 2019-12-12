#include "Sensor.h"
Vec3 Sensor::acceleration, Sensor::angularvelocity, Sensor::direction;
bool Sensor::debugMode;

void Sensor::initialize(bool debugMode) {	//初期化
	Sensor::debugMode = debugMode;
	acceleration = Vec3(0, 0, 0);	//加速度初期化
	angularvelocity = Vec3(0, 0, 0);//角速度初期化
	direction = Vec3(0, 0, 0);		//方向初期化
}
void Sensor::finalize() {		//終了化

}
void Sensor::update() {
	//デバッグモードじゃなければ終了
	if (!debugMode) {return;}
	//初期化
	acceleration = Vec3(0, 0, 0);	//加速度
	angularvelocity = Vec3(0, 0, 0);//角速度
	direction = Vec3(0, 0, 0);		//方向
	//加速度の代入
	if (MyKey::getUpKeyPressed()) {
		acceleration.y = 1;
	}
	if (MyKey::getDownKeyPressed()) {
		acceleration.y = -1;
	}
	if (MyKey::getLeftKeyPressed()) {
		acceleration.x = -1;
	}
	if (MyKey::getRightKeyPressed()) {
		acceleration.x = +1;
	}
	//方向の代入
	if (KeyW.pressed()) {
		direction.y = 1;
	}
	if (KeyS.pressed()) {
		direction.y = -1;
	}
	if (KeyD.pressed()) {
		direction.x = +1;
	}
	if (KeyA.pressed()) {
		direction.x = -1;
	}
}

void Sensor::debugPrint() {
	Print(U"加速度XYZ" + Format(acceleration));
	Print(U"角速度XYZ" + Format(angularvelocity));
	Print(U"方向XYZ" + Format(direction));
}

Vec3 Sensor::getAcceleration() {
	return acceleration;
}
Vec3 Sensor::getAngularvelocity() {
	return angularvelocity;
}
Vec3 Sensor::getDirection() {
	return direction;
}
//データの格納
void Sensor::setData(Vec3& accel, Vec3& angular, Vec3& dir) {
	acceleration = accel;
	angularvelocity = angular;
	direction = dir;
}