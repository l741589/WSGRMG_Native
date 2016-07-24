#include "HookUtils.h"
#include "stdafx.h"

std::list<HookTask*> hookTasks;
bool doHookLog = true;

HookTask* doHook(char*func, void*pf, void*pf_s) {
	hook_t*fd = new hook_t();
	HookTask* ht = new HookTask();
	ht->name = func;
	ht->func = pf;
	ht->fd = fd;
	ht->func_s = pf_s;
	hookTasks.push_back(ht);
	LOGE("%s: %x",func, pf_s);
	return ht;
}

void HookTask::doHook() {
	LOGE("start hook");
	//hook_a(fd, (unsigned long)func_s, name, func, func);
	hook(fd, getpid(), "libcocos2dcpp.", name, func, func);
}
