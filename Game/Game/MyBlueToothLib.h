#pragma once
#include <stdlib.h>
#include <string>

class MyBlueToothLib {
private:


public:
	// �w�肵�����O�̃|�[�g����������
	bool SearchPort(const std::string& searchname, std::string& portname);
};