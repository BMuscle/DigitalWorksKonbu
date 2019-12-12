#include "MySocketServer.h"

#define PORT 50000

TCPServer* MySocketServer::server;
bool MySocketServer::connected;
char MySocketServer::data[18];
Vec3 MySocketServer::vecData[3];//1つ２バイトでXYZの３種 ３つのセンサーが存在するので１８バイト

void MySocketServer::initialize() {	//初期化
	server = new TCPServer();
	server->startAccept(PORT);//接続待機
	connected = false;
	for (int i = 0; i < 3; i++) {
		vecData[i] = Vec3(0, 0, 0);
	}

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
		//データ変換

		//加速度
		vecData[0].x = ((data[0]  << 8) | data[1]);
		vecData[0].y = ((data[2]  << 8) | data[3]);
		vecData[0].z = ((data[4]  << 8) | data[5]);
		//ジャイロ
		vecData[1].x = ((data[6]  << 8) | data[7]);
		vecData[1].y = ((data[8]  << 8) | data[9]);
		vecData[1].z = ((data[10] << 8) | data[11]);
		//方向
		vecData[2].x = ((data[12] << 8) | data[13]);
		vecData[2].y = ((data[14] << 8) | data[15]);
		vecData[2].z = ((data[16] << 8) | data[17]);

		//デバッグ用
		Print(U"加速度受信データXYZ" + Format(vecData[0]));
		Print(U"角速度受信データXYZ" + Format(vecData[1]));
		Print(U"方向受信データXYZ" + Format(vecData[2]));
		Sensor::setData(vecData[0], vecData[1], vecData[2]);//データの受け渡し
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