#pragma once
#include <Siv3D.hpp>

class MyKey {
public:
	MyKey() = delete;
	static void isGamePad(void);
	static bool getDecisionKey(void);	//����L�[����
	static bool getReturnKey(void);		//�߂�L�[����
	static bool getUpKey(void);			//��L�[����
	static bool getDownKey(void);		//���L�[����
	static bool getLeftKey(void);		//���L�[����
	static bool getRightKey(void);		//�E�L�[����
	static void setKeyLock(bool lock);	//�L�[���͂�Lock����
private:
	static bool lock;
	static bool padflag;
};