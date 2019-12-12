#pragma once
#include <Siv3D.hpp>
#include "MyKey.h"
class Sensor {
private:
	//�����x�A�p���x�A����
	static Vec3 acceleration, angularvelocity, direction;
	static bool debugMode;//�f�o�b�O���[�h�������邩�ǂ����A�L�[���͂Œl����͂ł���悤�ɂȂ�B(�p���x���Ή�)
public:
	Sensor() = delete;
	static void initialize(bool debugMode = false);	//������
	static void finalize();		//�I����
	static void update();		//�f�o�b�O���[�h���̌v�Z����
	static Vec3 getAcceleration();//�����x��Ԃ�
	static Vec3 getAngularvelocity();//�p���x��Ԃ�
	static Vec3 getDirection();//������Ԃ�
};