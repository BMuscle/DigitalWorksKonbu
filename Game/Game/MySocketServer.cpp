#include "MySocketServer.h"

#define PORT 50000

TCPServer* MySocketServer::server;
bool MySocketServer::connected;
char MySocketServer::data[18];

void MySocketServer::initialize() {	//初期化
	server = new TCPServer();
	server->startAccept(PORT);//接続待機
	connected = false;

}
void MySocketServer::finalize() {		//終了化
	server->disconnect();//コネクション切断
	delete server;
}
void MySocketServer::update() {
	if (server->hasSession()) {//クライアントが接続してきたとき
		if (!connected) {//初接続の場合
			connected = true;
		}
		//データ送受信
		server->read(data);
		Print(data[17]);
		server->send(1);
	}

	if (connected && !server->hasSession()) {//クライアント側が切断
		server->disconnect();//一旦切断する
		connected = false;//コネクションフラグオフ
		server->startAccept(PORT);//接続待機
	}
}
bool MySocketServer::isConnection() {//現在接続されているかどうか
	return connected;
}