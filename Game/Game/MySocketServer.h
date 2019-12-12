#pragma once
#include <Siv3D.hpp>

class MySocketServer {
private:
	static TCPServer *server;
	static bool connected;
	static char data[18];
public:
	MySocketServer() = delete;
	static void initialize();	//‰Šú‰»
	static void finalize();		//I—¹‰»
	static void update();
	static bool isConnection();//Œ»İÚ‘±‚³‚ê‚Ä‚¢‚é‚©‚Ç‚¤‚©

};