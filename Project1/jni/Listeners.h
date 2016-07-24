#pragma once
#include "stdafx.h"

enum Step {
	buffSelfStep = 0,
	buffEnemyStep = 1,
	buffOverStep = 2,
	doCannonSupportStep = 3,
	doCannonSupportStepOver = 4,
	airAttackStep = 5,
	airRecoveryStep = 7,
	lockTargetStep = 8,
	antiSubStep = 9,
	openAntiSubRecoveryStep = 0xA,
	openTorpedoAttackStep = 0xB,
	openTorpedoRecoveryStep = 0xC,
	normalAttackStep = 0xD,
	normalAttack2Step = 0xE,
	closeTorpedoAttackStep = 0x12,
	closeTorpedoRecoveryStep = 0x13,
	showGameResult = 0x14,
	Notification = 0x16
};

enum AttackType {
	None=-1,
	Normal,
	Torpedo,
	Skill,
	Air,
	AntiSub
};

extern std::map<Step, const char*> StepNames;
extern std::map<AttackType, const char*> AttackTypeNames;
extern Step currentStep;
extern bool day;
void registerUpdateFunc(int tag, std::function<void(double)> func);
void unregisterUpdateFunc(int tag);