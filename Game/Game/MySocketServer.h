#pragma once
#include <Siv3D.hpp>
#include "Sensor.h"
class MySocketServer {
private:
	static TCPServer *server;
	static bool connected;
	static char data[18];
	static Vec3 vecData[3];//1�Q�o�C�g��XYZ�̂R�� �R�̃Z���T�[�����݂���̂łP�W�o�C�g
public:
	MySocketServer() = delete;
	static void initialize();	//������
	static void finalize();		//�I����
	static void update();
	static bool isConnection();//���ݐڑ�����Ă��邩�ǂ���

};