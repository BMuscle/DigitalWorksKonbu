#pragma once
#include <Siv3D.hpp>
#include "Sensor.h"
class MySocketServer {
private:
	static TCPServer *server;
	static bool connected;
	static char data[18];
	static Vec3 vecData[3];//1つ２バイトでXYZの３種 ３つのセンサーが存在するので１８バイト
public:
	MySocketServer() = delete;
	static void initialize();	//初期化
	static void finalize();		//終了化
	static void update();
	static bool isConnection();//現在接続されているかどうか

};