#pragma once

#include "stdafx.h"

class UserInfo {
public:
	std::string uid;
	std::string name;
	std::string server;

	std::string toJson();
};

class UserConfig {
public:
	UserConfig(const char*json);

	std::string uid;
	int doLog;

};

extern UserConfig*userConfig;
extern UserInfo*userInfo;
