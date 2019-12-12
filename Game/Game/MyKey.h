#pragma once
#include <Siv3D.hpp>

class MyKey {
public:
	MyKey() = delete;
	static void isGamePad(void);
	static bool getDecisionKey(void);	//決定キー入力
	static bool getReturnKey(void);		//戻るキー入力
	static bool getUpKeyPressed(void);			//上キー入力
	static bool getDownKeyPressed(void);		//下キー入力
	static bool getLeftKeyPressed(void);		//左キー入力
	static bool getRightKeyPressed(void);		//右キー入力

	static bool getUpKeyDown(void);			//上キー入力
	static bool getDownKeyDown(void);		//下キー入力
	static bool getLeftKeyDown(void);		//左キー入力
	static bool getRightKeyDown(void);		//右キー入力

	static void setKeyLock(bool lock);	//キー入力をLockする

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