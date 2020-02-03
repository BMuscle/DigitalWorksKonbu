#pragma once
#include <stdlib.h>
#include <string>

class MyBlueToothLib {
private:


public:
	// 指定した名前のポート名を見つける
	bool SearchPort(const std::string& searchname, std::string& portname);
};