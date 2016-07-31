#pragma once

#ifndef LOG_TAG
#define LOG_TAG "MagicBoxNative"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif

#ifndef LOGR
#define LOGR(...) logRemote(__FILE__,__LINE__,__VA_ARGS__)
#endif

#ifndef LOGER
#define LOGER(...) {LOGE(__VA_ARGS__);LOGR(__VA_ARGS__);}
#endif

#ifdef __cplusplus
extern "C" {
#endif
	void logRemote(const char*file, int line, const char*fmt, ...);
#ifdef __cplusplus
	}
#endif