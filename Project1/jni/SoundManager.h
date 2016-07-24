#pragma once
#include "stdafx.h"


class SoundManager {
private:
	std::map<std::string, std::string> map;
	std::string base;
	SoundManager();
	~SoundManager();
public:
	static SoundManager* getInstance();

	bool stop(std::string eventName);
	bool play(std::string eventName, std::string eventGroup = "", bool force=false);
};
