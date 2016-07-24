#pragma once

#include "adbi/util.h"
#include "adbi/base.h"
#include "adbi/hook.h"
#include <list>


struct HookTask {
	char*name;
	void*func;
	hook_t*fd;
	void*func_s;
	void doHook();
};

extern std::list<HookTask*> hookTasks;
extern bool doHookLog;

HookTask*doHook(char*func, void*pf, void*pf_s);

#define HOOK_LOG if (doLog) LOGE

#define HSQ(RET,func, ... ) HS(RET,func, __VA_ARGS__ )
#define HS(RET,func, ... )									\
	extern "C" void func();\
	RET F##func(__VA_ARGS__);								\
	HookTask*HT##func=doHook(#func,(void*)F##func,(void*)func);	\
	int C##func = 0;										\
    RET F##func(__VA_ARGS__) {								\
	++C##func;												\

#define HSUPER(doLog, func,...) \
	auto ret = _rsuper(HT##func->fd, F##func, __VA_ARGS__);		\
	if (doLog) LOGE("%s#%ld",#func,C##func);					\
	--C##func;												\

#define HE(func,...) _HE(true,func,__VA_ARGS__)
#define HEQ(func,...) _HE(false,func,__VA_ARGS__)
#define _HE(doLog,func, ... )								\
	_super(HT##func ->fd,F##func, __VA_ARGS__ );			\
	if (doLog) LOGE("%s#%ld",#func,C##func);					\
	--C##func;												\
}

#define HER(func,...) _HER(true,func,__VA_ARGS__)
#define HERQ(func,...) _HER(false,func,__VA_ARGS__)
#define _HER(doLog, func, ... )								\
	HSUPER(doLog,func,__VA_ARGS__)							\
	return ret;												\
}

template<class...ARGS>
void _super(hook_t*fd, void(*func)(ARGS...), ARGS...args) {
	hook_precall(fd);
	typedef void(*pf)(ARGS...);
	(reinterpret_cast<pf>((void*)fd->orig))(args...);
	hook_postcall(fd);
}

template<class...ARGS>
void _super(hook_t*fd, void(*func)(),nullptr_t) {
	hook_precall(fd);
	typedef void(*pf)();
	(reinterpret_cast<pf>((void*)fd->orig))();
	hook_postcall(fd);
}

template<class RET, class...ARGS>
RET _rsuper(hook_t*fd, RET(*func)(ARGS...), ARGS...args) {
	hook_precall(fd);
	typedef RET(*pf)(ARGS...);
	RET ret=(reinterpret_cast<pf>((void*)fd->orig))(args...);
	hook_postcall(fd);
	return ret;
}

template<class RET, class...ARGS>
RET _rsuper(hook_t*fd, RET(*func)(), nullptr_t) {
	hook_precall(fd);
	typedef RET(*pf)();
	RET ret = (reinterpret_cast<pf>((void*)fd->orig))();
	hook_postcall(fd);
	return ret;
}

/*
template<class RET, class...ARGS>
RET _rsuper(hook_t*fd, RET(*func)(),nullptr_t) {
	hook_precall(fd);
	typedef RET(*pf)();
	RET ret = (reinterpret_cast<pf>((void*)fd->orig))();
	hook_postcall(fd);
	return ret;
}
*/
