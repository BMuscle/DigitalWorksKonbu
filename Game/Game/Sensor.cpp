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
		acceleration.y = 100;
	}
	if (MyKey::getDownKeyPressed()) {
		acceleration.y = -100;
	}
	if (MyKey::getLeftKeyPressed()) {
		acceleration.x = -100;
	}
	if (MyKey::getRightKeyPressed()) {
		acceleration.x = +100;
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
	static int maxAccX = 0, maxAccY = 0, maxAccZ = 0;
	Print(U"�����xXYZ" + Format(acceleration));
	Print(U"�p���xXYZ" + Format(angularvelocity));
	Print(U"����XYZ" + Format(direction));

	maxAccX = Max((int)acceleration.x, maxAccX);
	maxAccY = Max((int)acceleration.y, maxAccY);
	maxAccZ = Max((int)acceleration.z, maxAccZ);

	Print(U"�ő�����xXYZ" + Format(maxAccX,U" ",maxAccY, U" ", maxAccZ));


	//Circle(Window::ClientWidth() / 2 + acceleration.x * 2, Window::ClientHeight() / 2 + acceleration.y * 2, 40).draw();
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
	//1G = 100�ŗ��Ă���̂�1G = 10�܂ŗ��Ƃ��i�l�̐؂藎�Ƃ��j
	acceleration.x /= 10;
	acceleration.y /= 10;
	acceleration.z /= 10;
}