#pragma once



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <jni.h>
#include <android/log.h>

#include <map>
#include <string>
#include <list>
#include <set>
#include <functional>
#include <vector>
#include "adbi/util.h"
#include "adbi/base.h"
#include "adbi/hook.h"
#include "decl.h"
#include "hookUtils.h"
#include "util.h"
#include "rapidjson/document.h"


jobject action(const char*action,const std::list<const char*>& args);
std::string action_s(const char*action,const std::list<const char*>& args);