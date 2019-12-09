#pragma once
#include <Siv3D.hpp>

class MyKey {
public:
	MyKey() = delete;
	static void isGamePad(void);
	static bool getDecisionKey(void);	//決定キー入力
	static bool getReturnKey(void);		//戻るキー入力
	static bool getUpKey(void);			//上キー入力
	static bool getDownKey(void);		//下キー入力
	static bool getLeftKey(void);		//左キー入力
	static bool getRightKey(void);		//右キー入力
	static void setKeyLock(bool lock);	//キー入力をLockする
private:
	static bool lock;
	static bool padflag;
};