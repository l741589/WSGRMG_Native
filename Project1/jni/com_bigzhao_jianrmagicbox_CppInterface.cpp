#include"com_bigzhao_jianrmagicbox_CppInterface.h"

#include "stdafx.h"
#include "Listeners.h"
#include "SoundManager.h"

JavaVM*jvm;
jclass CppInterface;
jclass String;
jmethodID CppInterface_action;

#define JNIENV

static void my_log(char *msg) {
	LOGE("%s", msg);
}

 JNIEnv *GetEnv()
{
	int status;
	JNIEnv *envnow = NULL;
	status = jvm->GetEnv((void **)&envnow, JNI_VERSION_1_6);
	if (status < 0)
	{
		status = jvm->AttachCurrentThread(&envnow, NULL);
		if (status < 0)
		{
			return NULL;
		}
	}
	return envnow;

}

jobject action(const char*action,const std::list<const char*>& args) {
	JNIEnv*jni_env = GetEnv();
	auto str = jni_env->NewStringUTF(action);
	auto arr=jni_env->NewObjectArray(args.size(), String, NULL);
	int i = 0;
	std::list<jobject> todelete;
	for (auto s : args) {
		auto ls = jni_env->NewStringUTF(s);
		todelete.push_back(ls);
		jni_env->SetObjectArrayElement(arr, i++, ls);
	}
	auto ret = jni_env->CallStaticObjectMethod(CppInterface, CppInterface_action, str, arr);
	for (auto s : todelete) jni_env->DeleteLocalRef(s);
	jni_env->DeleteLocalRef(str);
	jni_env->DeleteLocalRef(arr);
	return ret;
}

std::string action_s(const char*action, const std::list<const char*>& args) {
	JNIEnv*jni_env = GetEnv();
	auto obj = ::action(action, args);
	LOGE("action_s,%x", jni_env);
	const char*chars=jni_env->GetStringUTFChars((jstring)obj, NULL);
	std::string s(chars);
	LOGE("action_s: %s", s.c_str());
	jni_env->ReleaseStringUTFChars((jstring)obj, chars);
	//LOGE("ReleaseStringUTFChars");
	return s;
}

#define LOGREMOTELEN 16777216
char logRemoteBuffer[LOGREMOTELEN];
char logRemoteBuffer2[LOGREMOTELEN];
void logRemote(const char*file,int line,const char*fmt, ...) {
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsnprintf(logRemoteBuffer, LOGREMOTELEN, fmt, argptr);
	va_end(argptr);
	snprintf(logRemoteBuffer2, LOGREMOTELEN, "%s.%d: %s", file, line, logRemoteBuffer);
	action("logError", { logRemoteBuffer2 });
}

JNIEXPORT jobject JNICALL Java_com_bigzhao_jianrmagicbox_CppInterface_nativeAction
(JNIEnv *, jclass, jint action, jobjectArray) {
	if (action == 0) LOGE("native action test");
	return NULL;
}

std::string*createString(const char*str) {
	cocos2d::__String* s = cocos2d::__String::createWithFormat(str);
	return (std::string*)(s + 6);
}

std::string*createString(const std::string&str) {
	return createString(str.c_str());
}

extern "C" void* _ZN7cocos2d12TextureCache8addImageERKSs(void*t, void* s);
extern "C" cocos2d::Sprite* _ZN7cocos2d2ui12Scale9Sprite6createERKSs(std::string*file);
extern "C" int _ZN7cocos2d9FileUtils13addSearchPathERKSsb(cocos2d::FileUtils*t,std::string*path, bool front);

double c = 0;

JNIEXPORT void JNICALL Java_com_bigzhao_jianrmagicbox_CppInterface_init(JNIEnv *env, jclass cls) {
    LOGE("init");
	env->GetJavaVM(&jvm);
    set_logfunction(my_log);
	
	//_ZN7cocos2d9FileUtils13addSearchPathERKSsb(cocos2d::FileUtils::getInstance(), createString(""), true);
    for(HookTask*ht:hookTasks) ht->doHook();
	LOGE("hook done");
	String = env->FindClass("java/lang/String");
	String = (jclass)env->NewGlobalRef(String);
	CppInterface = (jclass)env->NewGlobalRef(cls);
	CppInterface_action = env->GetStaticMethodID(CppInterface, "action", "(Ljava/lang/String;[Ljava/lang/String;)Ljava/lang/Object;");
	//CppInterface_action = (jmethodID)env->NewGlobalRef(CppInterface_action);
	SoundManager::getInstance();
	

	registerUpdateFunc(0x6A74, [](double delta) {
		
		c += delta;
		LOGE("path time: %g",c);
		if (c < 0.5) return;
		unregisterUpdateFunc(0x6A74);
		std::string ext_files=action_s("getFilePath", {"ext_files:."});
		LOGE("path:%s", ext_files.c_str());
		_ZN7cocos2d9FileUtils13addSearchPathERKSsb(cocos2d::FileUtils::getInstance(), createString(ext_files + "/res/xml"), true);
		_ZN7cocos2d9FileUtils13addSearchPathERKSsb(cocos2d::FileUtils::getInstance(), createString(ext_files + "/res/ccbResources/live2D"), true);
		_ZN7cocos2d9FileUtils13addSearchPathERKSsb(cocos2d::FileUtils::getInstance(), createString(ext_files + "/res/audio"), true);
		_ZN7cocos2d9FileUtils13addSearchPathERKSsb(cocos2d::FileUtils::getInstance(), createString(ext_files + "/res/ccbResources"), true);
		_ZN7cocos2d9FileUtils13addSearchPathERKSsb(cocos2d::FileUtils::getInstance(), createString(ext_files + "/res"), true);				
		/*		auto*fu = cocos2d::FileUtils::getInstance();

#define TYPE std::string
		for (TYPE*i = *(TYPE**)(fu + 8); i < *(TYPE**)(fu + 9); ++i) {
			LOGE("path:%s", i->c_str());
		}*/
		//LOGE("get paths");
		//LOGE("path:%d,%d,%d", sizeof(std::string), sizeof(std::vector<int>), sizeof(std::vector<std::string>));
		//const std::vector<std::string>* paths=cocos2d::FileUtils::getInstance()->getSearchPaths();
		//LOGE("paths:%x,%x", *(int*)((int)paths + 4), *(int*)((int)paths + 8));
		//LOGE("paths:%s", ((std::string*)(*(int*)((int)paths + 4)+sizeof(std::string)))->c_str());
		//auto a1 = (int)paths;
		//LOGE("paths size:%d", *(int *)(a1 + 12) - *(int *)(a1 + 4) + 8 * (*(int *)(a1 + 8) - *(int *)a1));
	});
	
	//LOGR("test1 %s%d", "test", 2);
	
}
