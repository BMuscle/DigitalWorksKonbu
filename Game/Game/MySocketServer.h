#pragma once
#include <Siv3D.hpp>

class MySocketServer {
private:
	static TCPServer *server;
	static bool connected;
	static char data[18];
public:
	MySocketServer() = delete;
	static void initialize();	//������
	static void finalize();		//�I����
	static void update();
	static bool isConnection();//���ݐڑ�����Ă��邩�ǂ���

};