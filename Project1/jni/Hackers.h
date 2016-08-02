#pragma once

#include "stdafx.h"

class UserInfo {
public:
	std::string uid;
	std::string name;
	std::string server;
};

extern UserInfo*userInfo;