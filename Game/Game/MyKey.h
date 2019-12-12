#pragma once
#include <Siv3D.hpp>

class MyKey {
public:
	MyKey() = delete;
	static void isGamePad(void);
	static bool getDecisionKey(void);	//����L�[����
	static bool getReturnKey(void);		//�߂�L�[����
	static bool getUpKeyPressed(void);			//��L�[����
	static bool getDownKeyPressed(void);		//���L�[����
	static bool getLeftKeyPressed(void);		//���L�[����
	static bool getRightKeyPressed(void);		//�E�L�[����

	static bool getUpKeyDown(void);			//��L�[����
	static bool getDownKeyDown(void);		//���L�[����
	static bool getLeftKeyDown(void);		//���L�[����
	static bool getRightKeyDown(void);		//�E�L�[����

	static void setKeyLock(bool lock);	//�L�[���͂�Lock����

	enum class KEY {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		DECISION,
		RETURN,
	};
private:
	static bool lock;
	static bool padflag;
};