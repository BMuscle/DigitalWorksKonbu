#include "MySocketServer.h"

#define PORT 50000

TCPServer* MySocketServer::server;
bool MySocketServer::connected;
char MySocketServer::data[18];
Vec3 MySocketServer::vecData[3];//1�Q�o�C�g��XYZ�̂R�� �R�̃Z���T�[�����݂���̂łP�W�o�C�g

void MySocketServer::initialize() {	//������
	server = new TCPServer();
	server->startAccept(PORT);//�ڑ��ҋ@
	connected = false;
	for (int i = 0; i < 3; i++) {
		vecData[i] = Vec3(0, 0, 0);
	}

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
		//�f�[�^�ϊ�

		//�����x
		vecData[0].x = ((data[0]  << 8) | data[1]);
		vecData[0].y = ((data[2]  << 8) | data[3]);
		vecData[0].z = ((data[4]  << 8) | data[5]);
		//�W���C��
		vecData[1].x = ((data[6]  << 8) | data[7]);
		vecData[1].y = ((data[8]  << 8) | data[9]);
		vecData[1].z = ((data[10] << 8) | data[11]);
		//����
		vecData[2].x = ((data[12] << 8) | data[13]);
		vecData[2].y = ((data[14] << 8) | data[15]);
		vecData[2].z = ((data[16] << 8) | data[17]);

		//�f�o�b�O�p
		Print(U"�����x��M�f�[�^XYZ" + Format(vecData[0]));
		Print(U"�p���x��M�f�[�^XYZ" + Format(vecData[1]));
		Print(U"������M�f�[�^XYZ" + Format(vecData[2]));
		Sensor::setData(vecData[0], vecData[1], vecData[2]);//�f�[�^�̎󂯓n��
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