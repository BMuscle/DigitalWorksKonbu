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
	//������
	static void initialize(bool debugMode = false);	
	//�I����
	static void finalize();		
	//�f�o�b�O���[�h���̌v�Z����
	static void update();		
	//�f�o�b�O�p�̏o�́i�ȈՕ����A�}�`�j���s��
	static void debugPrint();
	//�����x��Ԃ�(Vec3)
	static Vec3 getAcceleration();
	//�p���x��Ԃ�(Vec3)
	static Vec3 getAngularvelocity();
	//������Ԃ�(Vec3)
	static Vec3 getDirection();
	//�Z���T�[�f�[�^�̊i�[
	static void setData(Vec3& accel, Vec3& angular, Vec3& dir);
};