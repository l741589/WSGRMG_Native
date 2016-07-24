#include "Listeners.h"
#include "FakeShip.h"
#include <mutex>
#include "audio/AudioEngine.h"

#define EP(e) {e,#e},
std::map<Step, const char*> StepNames = {
	EP(buffSelfStep)
	EP(buffEnemyStep)
	EP(buffOverStep)
	EP(doCannonSupportStep)
	EP(doCannonSupportStepOver)
	EP(airAttackStep)
	EP(airRecoveryStep)
	EP(lockTargetStep)
	EP(antiSubStep)
	EP(openAntiSubRecoveryStep)
	EP(openTorpedoAttackStep)
	EP(openTorpedoRecoveryStep)
	EP(normalAttackStep)
	EP(normalAttack2Step)
	EP(closeTorpedoAttackStep)
	EP(closeTorpedoRecoveryStep)
	EP(showGameResult)
	EP(Notification)
};

std::map<AttackType, const char*> AttackTypeNames = {
	{ None, "" },
	EP(Normal)
	EP(Torpedo)
	EP(Air)
	EP(Skill)
	EP(AntiSub)
};



std::map<int, std::function<void(double)>> updateFunc;
Step currentStep;
bool day = true;
char tmpbuf[65536];
int stepCounter = -1;

//Step
HS(void, _ZN10FightScene10updateStepEv, void*t)
int step = *(int*)(((char*)t) + 760);
currentStep = (Step)step;
++stepCounter;
LOGE("STEP %s", StepNames[currentStep]);
HE(_ZN10FightScene10updateStepEv, t);

//day battle
HS(int, _ZN10FightScene4initEPN9rapidjson15GenericDocumentINS0_4UTF8IcEENS0_19MemoryPoolAllocatorINS0_12CrtAllocatorEEES5_EE, void* a1, int a2)
day = true;
HER(_ZN10FightScene4initEPN9rapidjson15GenericDocumentINS0_4UTF8IcEENS0_19MemoryPoolAllocatorINS0_12CrtAllocatorEEES5_EE, a1, a2);

//night battle
HS(int, _ZN10FightScene13enterNightWarERKN9rapidjson12GenericValueINS0_4UTF8IcEENS0_19MemoryPoolAllocatorINS0_12CrtAllocatorEEEEE, void* a1, int a2)
day = false;
HER(_ZN10FightScene13enterNightWarERKN9rapidjson12GenericValueINS0_4UTF8IcEENS0_19MemoryPoolAllocatorINS0_12CrtAllocatorEEEEE,a1,a2);

//attack
HS(void, _ZN10FightScene16showNormalAttackEP4Shipi, void*t, Ship*ship, int x)
FackShip(ship, x>0).onAttack(Normal);
HE(_ZN10FightScene16showNormalAttackEP4Shipi, t, ship, x);

//sink
HS(int, _ZN4Ship14sinkToUnderSeaESt8functionIFvvEE, Ship* ship, int x)
LOGE("%d", x);
FackShip(ship, x>0).onSink();
HER(_ZN4Ship14sinkToUnderSeaESt8functionIFvvEE, ship, x);


//show damage
HS(int, _ZN10FightScene10showDamageE10DamageTypeii, void*t, int damageType, int cid, int y)
LOGE("DAMAGE:%d %d %d", damageType, cid, y);
FackShip(((FightScene*)t)->getShipByCid(cid), 0).onDamage(damageType);
HER(_ZN10FightScene10showDamageE10DamageTypeii, t, damageType, cid,y);

HS(int, _ZN10FightScene9showSkillEP4Shipii, void*t, Ship*ship, int x, int y)
LOGE("%d,%d",x, y);
FackShip(ship, x > 0).onAttack(Skill);
HER(_ZN10FightScene9showSkillEP4Shipii, t, ship, x, y)

HS(int, _ZN10FightScene19showAirAttackEffectEP4Shipi, void*t, Ship*ship, int x)
LOGE("%d", x);
FackShip s(ship, x > 0);
s.onAttack(Air);
HER(_ZN10FightScene19showAirAttackEffectEP4Shipi, t, ship, x);

HS(int, _ZN17CombatResultLayer10ConfigInfoEv, void*t)
HER(_ZN17CombatResultLayer10ConfigInfoEv, t);

HS(int, _ZN12NewShipLayer12onNodeLoadedEPN7cocos2d4NodeEPN12cocosbuilder10NodeLoaderE, void*node, void*nodeLoader)
HER(_ZN12NewShipLayer12onNodeLoadedEPN7cocos2d4NodeEPN12cocosbuilder10NodeLoaderE, node, nodeLoader);

HS(int, _ZN12MarryOKLayer9InitLayerEv, int a)
HER(_ZN12MarryOKLayer9InitLayerEv, a);

HS(int, _ZN9MainLayer13shipIconTouchEN7cocos2d4Vec2E, int t, int y)
HER(_ZN9MainLayer13shipIconTouchEN7cocos2d4Vec2E, t, y);

HS(void, _ZN26CampaignCombatPrepareLayer20ConfigFormationLayerEv, void*t)
HE(_ZN26CampaignCombatPrepareLayer20ConfigFormationLayerEv, t);

HS(int, _ZN18CombatPrepareLayer20ConfigFormationLayerEv, void*t)
HER(_ZN18CombatPrepareLayer20ConfigFormationLayerEv, t);

HS(int, _ZN24PEventCombatPrepareLayer20ConfigFormationLayerEv, void*t)
HER(_ZN24PEventCombatPrepareLayer20ConfigFormationLayerEv, t);

HS(int, _ZN21PVPCombatPrepareLayer20ConfigFormationLayerEv, void*t)
HER(_ZN21PVPCombatPrepareLayer20ConfigFormationLayerEv, t);



void GetPng(int cid,int skin, int type) {
	LOGE("Get L %s %d,%d",type==0?"Normal":"Broken", cid, skin);
	if (C_ZN17CombatResultLayer10ConfigInfoEv > 0) FackShip(cid, skin).onMVP();
	if (C_ZN12NewShipLayer12onNodeLoadedEPN7cocos2d4NodeEPN12cocosbuilder10NodeLoaderE > 0) FackShip(cid, skin).onNew();
	if (C_ZN12MarryOKLayer9InitLayerEv > 0) FackShip(cid,skin).onMarry();
	if (C_ZN9MainLayer13shipIconTouchEN7cocos2d4Vec2E>0) FackShip(cid, skin).onTouch();
	if (C_ZN26CampaignCombatPrepareLayer20ConfigFormationLayerEv > 0 || C_ZN18CombatPrepareLayer20ConfigFormationLayerEv > 0
		|| C_ZN24PEventCombatPrepareLayer20ConfigFormationLayerEv > 0 || C_ZN21PVPCombatPrepareLayer20ConfigFormationLayerEv > 0) {
		FackShip(cid, skin).onFormation();
	}
}

HS(int, _ZN9UIManager13getLNormalPngEii, int a1, int a2, int cid, int skin)
GetPng(cid, skin, 0);
HER(_ZN9UIManager13getLNormalPngEii, a1, a2, cid, skin);


HS(int, _ZN9UIManager13getLBrokenPngEii, int a1, int a2, int cid, int skin)
GetPng(cid, skin, 1);
HER(_ZN9UIManager13getLBrokenPngEii, a1, a2, cid, skin);

HS(int, _ZN9UIManager13getLNormalPngEPN11UserManager12UserShipDataE, int a1, int a2, int a3)
GetPng(*(int*)(a3 + 8), *(int*)(a3 + 72), 0);
HER(_ZN9UIManager13getLNormalPngEPN11UserManager12UserShipDataE, a1, a2, a3);

HS(int, _ZN9UIManager13getLBrokenPngEPN11UserManager12UserShipDataE, int a1, int a2, int a3)
GetPng(*(int*)(a3 + 8), *(int*)(a3 + 72), 0);
HER(_ZN9UIManager13getLBrokenPngEPN11UserManager12UserShipDataE, a1, a2, a3);

HS(int, _ZN9UIManager13getLNormalPngEi, int a1, int a2, int cid)
GetPng(cid, 0, 0);
HER(_ZN9UIManager13getLNormalPngEi, a1, a2, cid);


HS(int, _ZN9UIManager13getLBrokenPngEi, int a1, int a2, int cid)
GetPng(cid, 0, 0);
HER(_ZN9UIManager13getLBrokenPngEi, a1, a2, cid);

HS(void, _ZN4Ship8castBuffEiiRSt6vectorIiSaIiEE, int a, int b, int c, int d)
FackShip((Ship*)a,0).onBuff();
HE(_ZN4Ship8castBuffEiiRSt6vectorIiSaIiEE,a,b,c,d);


int torpedoStepCritic = -1;
HS(int, _ZN4Ship13torpedoAttackERKSt4listIPS_SaIS1_EERK10AttackInfob, int*t, void* list, int b)
if (stepCounter != torpedoStepCritic) {
	if (FackShip((Ship*)t, true).onAttack(Torpedo)) torpedoStepCritic = stepCounter;
	//for (auto*s : *list) LOGE("TORPEDO TARGET: %s", FackShip(s,1).desc());
}
HER(_ZN4Ship13torpedoAttackERKSt4listIPS_SaIS1_EERK10AttackInfob, t, list, b);

int antisubStepCritic = -1;
HS(int, _ZN4Ship13antiSubAttackERSt4listIPS_SaIS1_EERK10AttackInfo, int*t, void*list, int b)
if (currentStep == Step::antiSubStep) {
	if (stepCounter != antisubStepCritic) {
		if (FackShip((Ship*)t, true).onAttack(AntiSub)) antisubStepCritic = stepCounter;
	}
	//LOGE("ANTISUB:%s", FackShip((Ship*)t, true).desc());
} else {
	FackShip((Ship*)t,true).onAttack(AntiSub);
}
HER(_ZN4Ship13antiSubAttackERSt4listIPS_SaIS1_EERK10AttackInfo, t, list, b);

/*
HS(int, _ZN10NetManager23SendStartExploreRequestEii, void*t, int eid, int fid)
LOGE("fid:%ld", fid);
auto cid = getShipInFleet(fid, 0);
if (cid >0) FackShip(cid, 0).onExplore(0);
HER(_ZN10NetManager23SendStartExploreRequestEii, t, eid, fid);*/

/*
HS(int, _ZN24ExploreCombatResultLayer10ConfigInfoEv, void*t)
HER(_ZN24ExploreCombatResultLayer10ConfigInfoEv, t);


HS(int, _ZN11UserManager17getIndexFleetInfoEi, void*r, void*t, int fid)
HSUPER(false, _ZN11UserManager17getIndexFleetInfoEi, r, t, fid)
if (C_ZN24ExploreCombatResultLayer10ConfigInfoEv > 0) {
	auto fi = *(UserManager::FleetInfo*)r;
	auto sptr = fi.shipStartPtr;
	if (sptr >= fi.shipEndPtr) return ret;
	auto ship = UserManager::getInstance()->getIndexUserShip(*sptr);
	if (ship == nullptr) return ret;
	FackShip(ship->cid, 0).onExplore(1);
}
return ret;
}*/

HS(int, _ZN10NetManager14SendRepairBoatEii, int did, int sid)
auto ship = UserManager::getInstance()->getIndexUserShip(sid);
FackShip(ship->cid, 0).onRepair();
HER(_ZN10NetManager14SendRepairBoatEii, did, sid)


HS(int, _ZN10NetManager14SendChangeBoatEiii, void* t, int fid, int sid,int pos)
auto ship=UserManager::getInstance()->getIndexUserShip(sid);
if (ship != nullptr) FackShip(ship->cid, 0).onChange(fid,pos);
HER(_ZN10NetManager14SendChangeBoatEiii, t, fid, sid,pos);


//////////////////////////////////////////////////
double lastTime = 0;
std::recursive_mutex updateFuncMutex;
void registerUpdateFunc(int tag, std::function<void(double)> func) {
	updateFuncMutex.lock();
	updateFunc[tag] = func;
	updateFuncMutex.unlock();
}

void unregisterUpdateFunc(int tag) {	
	updateFuncMutex.lock();
	updateFunc[tag] = nullptr;
	updateFuncMutex.unlock();
}

HSQ(int64_t, _ZN7cocos2d8Director9drawSceneEv, int a)
do {
	if (updateFuncMutex.try_lock()) {
		double time = cocos2d::utils::gettime();
		if (lastTime == 0) {
			lastTime = time;
			updateFuncMutex.unlock();
			break;
		}
		auto delta = time - lastTime;
		lastTime = time;
		std::list<int> toremove;
		for (auto e : updateFunc) {
			if (e.second) e.second(delta);
			else toremove.push_back(e.first);
		}
		for (auto e : toremove) updateFunc.erase(e);
		updateFuncMutex.unlock();
	}
} while (false);
HERQ(_ZN7cocos2d8Director9drawSceneEv, a)

HS(void, _ZN7cocos2d12experimental11AudioEngine3endEv, void)
cocos2df::experimental::AudioEngine::end();
HE(_ZN7cocos2d12experimental11AudioEngine3endEv, nullptr)
