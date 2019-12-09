#include "MyKey.h"

bool MyKey::lock = false;
bool MyKey::padflag;

void MyKey::isGamePad() {
	if (Gamepad(0).isConnected()) {
		padflag = true;
	}
	else {
		padflag = false;
	}
}
bool MyKey::getDecisionKey(void) {
	if (!lock) {
		if (padflag) {
			return
				Gamepad(0).buttons[0].down() ||
				Gamepad(0).buttons[1].down() ||
				Gamepad(0).buttons[2].down() ||
				Gamepad(0).buttons[3].down();
		}
		else {
			return KeyEnter.down();
		}
	}
	return false;
}
bool MyKey::getReturnKey(void) {
	if (!lock) {
		if (padflag) {
			return
				Gamepad(0).buttons[4].down() ||//リターンキー
				Gamepad(0).buttons[5].down() ||//
				Gamepad(0).buttons[6].down() ||//
				Gamepad(0).buttons[7].down();  //
		}
		else {
			return KeyBackspace.down();
		}
	}
	return false;
}
bool MyKey::getUpKey(void) {
	if (!lock) {
		if (padflag) {
			//return Gamepad(0).buttons[13].down();
			if (Gamepad(0).axes[1] <= -1.0) {
				return true;
			}
			return false;//上
		}
		else {
			return KeyUp.pressed();
		}
	}
	return false;
}
bool MyKey::getDownKey(void) {
	if (!lock) {
		if (padflag) {
			if (Gamepad(0).axes[1] >= 1.0) {
				return true;
			}
			return false;//上
		}
		else {
			return KeyDown.pressed();
		}
	}
	return false;
}

bool MyKey::getLeftKey(void) {
	if (!lock) {
		if (padflag) {
			if (Gamepad(0).axes[0] <= -1.0) {
				return true;
			}
			return false;
		}
		else {
			return KeyLeft.pressed();
		}
	}
	return false;
}

bool MyKey::getRightKey(void) {
	if (!lock) {
		if (padflag) {
			if (Gamepad(0).axes[0] >= 1.0) {
				return true;
			}
			return false;
		}
		else {
			return KeyRight.pressed();
		}
	}
	return false;
}

void MyKey::setKeyLock(bool lock) {
	MyKey::lock = lock;
}