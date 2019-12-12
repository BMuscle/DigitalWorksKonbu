#include "Sensor.h"
Vec3 Sensor::acceleration, Sensor::angularvelocity, Sensor::direction;
bool Sensor::debugMode;

void Sensor::initialize(bool debugMode) {	//������
	Sensor::debugMode = debugMode;
	acceleration = Vec3(0, 0, 0);	//�����x������
	angularvelocity = Vec3(0, 0, 0);//�p���x������
	direction = Vec3(0, 0, 0);		//����������
}
void Sensor::finalize() {		//�I����

}
void Sensor::update() {
	//�f�o�b�O���[�h����Ȃ���ΏI��
	if (!debugMode) {return;}
	//������
	acceleration = Vec3(0, 0, 0);	//�����x
	angularvelocity = Vec3(0, 0, 0);//�p���x
	direction = Vec3(0, 0, 0);		//����
	//�����x�̑��
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
	//�����̑��
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
	Print(U"�����xXYZ" + Format(acceleration));
	Print(U"�p���xXYZ" + Format(angularvelocity));
	Print(U"����XYZ" + Format(direction));
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
//�f�[�^�̊i�[
void Sensor::setData(Vec3& accel, Vec3& angular, Vec3& dir) {
	acceleration = accel;
	angularvelocity = angular;
	direction = dir;
}