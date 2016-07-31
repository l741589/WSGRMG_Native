#pragma once
#include "stdafx.h"
#include "Listeners.h"

class FackShip {
private:
	char _desc[256];
public:
	int skin;
	bool day;
	int index;
	int sid;
	int cid;
	int hp;
	int hpMax;
	
	Step step;
	bool self;

	FackShip(Ship*ship, bool self);

	FackShip(int cid, int skin);

	const char*desc() {
		return _desc;
	}

	bool onAttack(AttackType attackType = Normal);
	bool onSink();
	bool onMVP();
	bool onNew();
	bool onMarry();
	bool onTouch();

	bool onTouchWithType(const char*group, const char*type);

	bool onDamage(int damageType);
	bool onBuff();
	bool onExplore(int state);
	bool onRepair();
	bool onFormation();
	bool onChange(int fid, int pos);
	bool onLive2dTouch(const char* name);
};