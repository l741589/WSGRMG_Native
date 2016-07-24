#include "FakeShip.h"
#include "audio/AudioEngine.h"
#include "SoundManager.h"

#define SOUND_PATH "/storage/0403-0201/Android/data/com.bigzhao.jianrmagicbox/files/MagicBox/test_sound/"


void testPlay(int x) {
	x %= 4;
	switch (x) {
	case 0:cocos2df::experimental::AudioEngine::play2d(SOUND_PATH"Ayanami_v1.mp3"); break;
	case 1:cocos2df::experimental::AudioEngine::play2d(SOUND_PATH"Ayanami_v2.mp3"); break;
	case 2:cocos2df::experimental::AudioEngine::play2d(SOUND_PATH"Ayanami_v3.mp3"); break;
	case 3:cocos2df::experimental::AudioEngine::play2d(SOUND_PATH"Ayanami_v4.mp3"); break;
	}
}

#define PLAYF(groupName,...) SoundManager::getInstance()->play(format( __VA_ARGS__ ),groupName,true)
#define PLAYG(groupName,...) SoundManager::getInstance()->play(format( __VA_ARGS__ ),groupName)
#define PLAY( ... ) SoundManager::getInstance()->play(format( __VA_ARGS__ ))
#define STOP( ... ) SoundManager::getInstance()->stop(format( __VA_ARGS__ ))

FackShip::FackShip(Ship*ship, bool self) {
	index = ship->getIndex();
	sid = ship->getShipId();
	cid = ship->getCid();
	skin = ship->getSkinCid();
	step = currentStep;
	hp = ship->getHP();
	hpMax = ship->getHPMax();
	day = ::day;
	this->self = self;
	snprintf(_desc, 256, "SHIP[%d,%d,%d,%d] %d/%d %s %s %s",
		index, sid, cid, skin,
		hp, hpMax,
		StepNames[step],
		day ? "DAY" : "NIGHT",
		self ? "SELF" : "ENEMY");
}

FackShip::FackShip(int cid, int skin) {
	index = -1;
	sid = cid;
	this->cid = cid;
	step = currentStep;
	day = ::day;
	this->skin = skin;
	this->self = true;
	hp = hpMax = 0;
	sprintf(_desc, "SHIP[%d,%d,%d] %s %s %s",
		index, sid, cid,
		StepNames[step],
		day ? "DAY" : "NIGHT",
		self ? "SELF" : "ENEMY");
}

bool FackShip::onAttack(AttackType attackType /*= Normal*/) {
	LOGE("%s ATK %s", AttackTypeNames[attackType], desc());
	if (this->day) {
		if (this->step == Step::normalAttackStep) {
			if (attackType == Skill) if (PLAY("%ld.attack.skill", cid)) return true;
			if (attackType == AntiSub) {
				if (PLAY("%ld.attack.antisub.1")) return true;
				if (PLAY("%ld.attack.antisub.first")) return true;
				if (PLAY("%ld.attack.antisub")) return true;
			}
			if (PLAY("%ld.attack.first", cid)) return true;
			if (PLAY("%ld.attack.1", cid)) return true;
		} else if (this->step == Step::normalAttack2Step) {
			if (attackType == Skill) if (PLAY("%ld.attack.skill", cid)) return true;
			if (attackType == AntiSub) {
				if (PLAY("%ld.attack.antisub.2")) return true;
				if (PLAY("%ld.attack.antisub.second")) return true;
				if (PLAY("%ld.attack.antisub")) return true;
			}
			if (PLAY("%ld.attack.second", cid)) return true;
			if (PLAY("%ld.attack.2", cid)) return true;
		} else if (this->step == Step::airAttackStep) {
			if (PLAY("%ld.attack.air", cid)) return true;
		} else if (this->step == Step::openTorpedoAttackStep) {
			if (PLAY("%ld.attack.torpedo.open", cid)) return true;
			if (PLAY("%ld.attack.torpedo", cid)) return true;
		} else if (this->step == Step::closeTorpedoAttackStep) {
			if (PLAY("%ld.attack.torpedo.close", cid)) return true;
			if (PLAY("%ld.attack.torpedo", cid)) return true;
		} else if (this->step == Step::antiSubStep) {
			if (PLAY("%ld.attack.antisub.open")) return true;
			if (PLAY("%ld.attack.antisub")) return true;
		}
	} else {
		if (attackType == Skill) if (PLAY("%ld.attack.skill", cid)) return true;
		if (attackType == AntiSub) {
			if (PLAY("%ld.attack.antisub.night")) return true;
			if (PLAY("%ld.attack.antisub.3")) return true;			
			if (PLAY("%ld.attack.antisub.third")) return true;
			if (PLAY("%ld.attack.antisub")) return true;
		}
		if (PLAY("%ld.attack.night", cid)) return true;
		if (PLAY("%ld.attack.third", cid)) return true;
		if (PLAY("%ld.attack.3", cid)) return true;
	}
	if (PLAY("%ld.attack", cid)) return true;
	if (PLAY("%ld.attack.1", cid)) return true;
	if (PLAY("%ld.attack.2", cid)) return true;
	return false;
}

bool FackShip::onSink() {
	std::string group = format("%ld.damage", cid);
	LOGE("SINK %s", desc());
	return PLAYF(group.c_str(), "%ld.sink", cid);
}

bool FackShip::onMVP() {
	LOGE("MVP %s", desc());
	return PLAY("%ld.mvp", cid);
}

bool FackShip::onNew() {
	LOGE("NEW %s", desc());
	return PLAY("%ld.new", cid);
}

bool FackShip::onMarry() {
	LOGE("MARRAY %s", desc());
	return PLAY("%ld.marry", cid);
}

bool FackShip::onTouch() {
	LOGE("TOUCH %s", desc());
	std::string group = format("%ld.touch", cid);
	long time = UserManager::getInstance()->getServerTime();
	auto t = gmtime(&time);
	int h = t->tm_hour + 8;
	if (h >= 18 || h < 6) {
		if (onTouchWithType(group.c_str(), ".night")) return true;
	} else {
		if (onTouchWithType(group.c_str(), ".day")) return true;
	}
	if (onTouchWithType(group.c_str(), "")) return true;
	return false;
}

bool FackShip::onTouchWithType(const char*group, const char*type) {
	std::set<int> ss = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < 10; ++i) {
		int x = 1 + rand() % ss.size();
		if (PLAYG(group, "%ld.touch%s.%d", cid,type, x))return true;
		else ss.erase(x);
	}
	if (PLAYG(group, "%ld.touch%s", cid, type)) return true;
	if (PLAYG(group, "%ld.touch%s.0", cid, type)) return true;
	return false;
}

bool FackShip::onDamage(int damageType) {
	LOGE("DAMAGE: %s", desc());
	if (this->hp == 0) return false;
	std::string group = format("%ld.damage", cid);
	if (hp*5 >= hpMax) {
		if (PLAYG(group.c_str(), "%ld.damage.medium", cid)) return true;
	} else if (damageType==0) {
		if (PLAYG(group.c_str(), "%ld.damage.big", cid)) return true;
	}
	if (PLAYG(group.c_str(), "%ld.damage", cid)) return true;
	return false;
}

bool FackShip::onBuff() {
	LOGE("BUFF %s", desc());
	return PLAY("%ld.buff", cid);
}

bool FackShip::onExplore(int state) {
	LOGE("EXPLORE %s", desc());
	std::string group = format("%ld.explore", cid);
	if (state == 0) {
		if (PLAYG(group.c_str(), "%ld.explore.start", cid)) return true;
	} else if (state == 1) {
		if (PLAYG(group.c_str(), "%ld.explore.finish", cid)) return true;
	}
	if (PLAYG(group.c_str(), "%ld.explore", cid)) return true;
	return false;
}

bool FackShip::onRepair() {
	LOGE("REPAIR %s", desc());
	return PLAY("%ld.repair", cid);
}

bool FackShip::onFormation() {
	return PLAY("%ld.formation", cid);
}

bool FackShip::onChange(int fid, int pos) {
	if (fid == 1 && pos == 1) {
		if (PLAY("%ld.change.flagship", cid)) return true;
	}
	return PLAY("%ld.change",cid);
}

