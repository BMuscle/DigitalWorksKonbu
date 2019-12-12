#include "MySocketServer.h"

#define PORT 50000

TCPServer* MySocketServer::server;
bool MySocketServer::connected;
char MySocketServer::data[18];

void MySocketServer::initialize() {	//������
	server = new TCPServer();
	server->startAccept(PORT);//�ڑ��ҋ@
	connected = false;

}
void MySocketServer::finalize() {		//�I����
	server->disconnect();//�R�l�N�V�����ؒf
	delete server;
}
void MySocketServer::update() {
	if (server->hasSession()) {//�N���C�A���g���ڑ����Ă����Ƃ�
		if (!connected) {//���ڑ��̏ꍇ
			connected = true;
		}
		//�f�[�^����M
		server->read(data);
		Print(data[17]);
		server->send(1);
	}

	if (connected && !server->hasSession()) {//�N���C�A���g�����ؒf
		server->disconnect();//��U�ؒf����
		connected = false;//�R�l�N�V�����t���O�I�t
		server->startAccept(PORT);//�ڑ��ҋ@
	}
}
bool MySocketServer::isConnection() {//���ݐڑ�����Ă��邩�ǂ���
	return connected;
}