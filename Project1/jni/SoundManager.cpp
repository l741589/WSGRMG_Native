#include "SoundManager.h"
#include <dirent.h>
#include <sys/stat.h>
#include "rapidjson/reader.h"
#include <string.h>
#include "util.h"
#include "audio/AudioEngine.h"

SoundManager*instance = nullptr;



SoundManager::SoundManager() {
	std::string json=action_s("buildSoundMap", {  });
	rapidjson::Document doc;
	LOGE("before parse");
	doc.Parse(json.c_str());
	LOGE("after parse");
	auto&map = doc["map"];
	if (map.IsNull()) return;
	for (auto i = map.MemberBegin(); i != map.MemberEnd(); ++i) {
		this->map[i->name.GetString()] = i->value.GetString();
		LOGE("%s -> %s", i->name.GetString(), i->value.GetString());
	}
	LOGE("map size: %ld", this->map.size());
	
}


SoundManager::~SoundManager() {
}

SoundManager* SoundManager::getInstance() {
	if (instance == nullptr) instance = new SoundManager();
	return instance;
}

std::map<std::string,int> playing;

bool SoundManager::stop(std::string eventGroup) {
	if (playing.find(eventGroup) == playing.end()) return true;
	auto aid = playing[eventGroup];
	if (aid == -1) return true;
	cocos2df::experimental::AudioEngine::stop(aid);
	playing.erase(eventGroup);
	return true;
}


bool SoundManager::play(std::string eventName,std::string eventGroup,bool force) {
	//if (lastStep>=0&&lastStep == stepCounter) return true;
	LOGE("try play:%s", eventName.c_str());
	if (eventGroup == "") eventGroup = eventName;
	if (map.find(eventName) == map.end()) return false;
	if (playing.find(eventGroup) != playing.end()) {
		if (force) stop(eventGroup);
		else return true;
	}
	int audioid=cocos2df::experimental::AudioEngine::play2d(map[eventName]);
	if (audioid == -1) return false;
	playing[eventGroup] = audioid;
	cocos2df::experimental::AudioEngine::setFinishCallback(audioid, [=](int aid,std::string path) {
		playing.erase(eventGroup);
	});
	return true;
}

