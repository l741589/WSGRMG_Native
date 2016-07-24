#pragma once
/*
 *  Collin's Binary Instrumentation Tool/Framework for Android
 *  Collin Mulliner <collin[at]mulliner.org>
 *  http://www.mulliner.org/android/
 *
 *  (c) 2012,2013
 *
 *  License: LGPL v2.1
 *
 */
#ifdef __cplusplus
extern "C" {
#endif
	void* set_logfunction(void(*func)(char *));
#ifdef __cplusplus
}
#endif