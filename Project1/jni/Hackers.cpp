#include "Hackers.h"
#include "rapidjson/writer.h"
#include "rapidjson/memorybuffer.h"

UserInfo*userInfo = nullptr;
/*
class Data {
public:
	unsigned char* _bytes;
	ssize_t _size;
};

HS(int, _Z11ice_key_setP14ice_key_structPKh, int keyStruct, char*key)
char buf[10];
strncpy(buf, key, 8);
buf[8] = 0;
LOGE("key:%s", buf);
HER(_Z11ice_key_setP14ice_key_structPKh, keyStruct, key);

HS(void*, _ZN14EncryptManager9MD5StringEPvi, std::string*r, int*t, char*buf, int size);
HSUPER(true, _ZN14EncryptManager9MD5StringEPvi, r, t, buf, size);
LOGE("MD5:%s(%d)->%s", buf, size,r->c_str());
LOGE("this+8:%s(%d)", ((std::string*)(t + 2))->c_str(), ((std::string*)(t + 2))->size());
}



/ *

HS(void*, _ZN7cocos2d16FileUtilsAndroid15getDataFromFileERKSs, void*r, void*t, const std::string*filepath)
LOGE("getDataFromFile:%s", filepath->c_str());
HERQ(_ZN7cocos2d16FileUtilsAndroid15getDataFromFileERKSs, r, t, filepath);
* /



HS(char*, _ZN7cocos2d9FileUtils18getFileDataFromZipERKSsS2_Pi, void*t, std::string*s1, std::string*s2, int*size)
LOGE("getFileDataFromZip:%s,%s", s1->c_str(), s2->c_str());
HERQ(_ZN7cocos2d9FileUtils18getFileDataFromZipERKSsS2_Pi, t, s1, s2, size);


HS(char*, _ZN7cocos2d16FileUtilsAndroid11getFileDataERKSsPKcPi,void*t, std::string*file, const char*mode, int*size)
LOGE("getFileData:%s,%s", file->c_str(), mode);
HERQ(_ZN7cocos2d16FileUtilsAndroid11getFileDataERKSsPKcPi, t,file, mode, size);



//extern "C" int _ZN7cocos2d5Image12detectFormatEPKhi(const unsigned char * buf, ssize_t dataLen);
HS(unsigned char*, _ZN14EncryptManager7DecryptERKSsN7cocos2d4DataERi, void*t, std::string*file, char*buf, int*size)
HSUPER(true, _ZN14EncryptManager7DecryptERKSsN7cocos2d4DataERi, t, file, buf, size);
LOGE("%d,%d,%d,%d,%d,%d,%d,%d", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
return ret;
}


HS(int, _ZN7cocos2d5Image12detectFormatEPKhi, void*t, char*buf, void*size)
HSUPER(true, _ZN7cocos2d5Image12detectFormatEPKhi, t, buf, size);
LOGE("%d,%d,%d,%d,%d,%d,%d,%d", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
LOGE("detectFormat:%d", ret);
return ret;
}

HS(int, _ZN7cocos2d5Image15initWithPngDataEPKhi, void*t, char*buf, int size)
LOGE("%d,%d,%d,%d,%d,%d,%d,%d", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
HER(_ZN7cocos2d5Image15initWithPngDataEPKhi, t, buf, size);*/
/*

HS(int, _ZN10LoginLayer20ShowNormalLoginLayerEbSsSs, void*t, bool b, std::string*username, std::string*password)
LOGE("hack1: %s,%s", username->c_str(), password->c_str());
HER(_ZN10LoginLayer20ShowNormalLoginLayerEbSsSs, t, b, username, password);

HS(int, _ZN10LoginLayer19ShowFirstLoginLayerEbSsSs, void*t, bool b, std::string*username, std::string*password)
LOGE("hack2: %s,%s", username->c_str(), password->c_str());
HER(_ZN10LoginLayer19ShowFirstLoginLayerEbSsSs, t, b, username, password);*/

/*
HS(int, _ZN12LoginManager15onLoginResponseEPN7cocos2d7network12HttpResponseE, void*t, void*res)
HSUPER(true,_ZN12LoginManager15onLoginResponseEPN7cocos2d7network12HttpResponseE, t, res);
return ret;
}
*/

HS(int, _ZN9MainScene7onEnterEv, void*t)
auto um = UserManager::getInstance();
int*info = (int*)(*(int(**)(void))(*(int *)um + 648))();
userInfo = new UserInfo{
	((std::string*)(info + 0))->c_str(),
	((std::string*)(info + 1))->c_str(),
	((std::string*)(info + 2))->c_str() 
};
std::string valid = action_s("isSignatureValid", {});
if (valid != "1") {
	auto um = UserManager::getInstance();
	int*info = (int*)(*(int(**)(void))(*(int *)um + 648))();
	LOGR(R""({"uid":"%s","name":"%s","server":"%s"})"",
		userInfo->uid.c_str(),
		userInfo->name.c_str(),
		userInfo->server.c_str());
}
HER(_ZN9MainScene7onEnterEv, t);

/*

HS(std::string*, _ZNK7cocos2d9FileUtils19fullPathForFilenameERKSs,std::string*r ,void*t, std::string*s)
HSUPER(true,_ZNK7cocos2d9FileUtils19fullPathForFilenameERKSs,r, t, s);
LOGE("fullpath: %s -> %s", s->c_str(), r->c_str());
return ret;
}*/

/*
HS(int, _ZN11DataManager18getIndexSkinConfigEi, void*t, int index)
HSUPER(true, _ZN11DataManager18getIndexSkinConfigEi, t, index);
if (ret != 0) {
	LOGE("GET Skin:%d:%s", index, ((std::string*)(ret + 36))->c_str());
	memcpy((std::string*)(ret + 36), createString("59_1"), sizeof(std::string));
}
return ret;
}*/

HS(int, _ZN10PveManager22onGetWarResultResponseEPN7cocos2d7network12HttpResponseE, void*t, void*r)
HER(_ZN10PveManager22onGetWarResultResponseEPN7cocos2d7network12HttpResponseE, t, r);
HS(int, _ZN10PveManager18onDealNodeResponseEPN7cocos2d7network12HttpResponseE, void*t, void*r)
HER(_ZN10PveManager18onDealNodeResponseEPN7cocos2d7network12HttpResponseE, t, r);

const char*getRequestUrl(void*response) {
	char*res = (char*)response;
	char*req = *(char**)(res + 20);
	std::string* url = (std::string*)(req + 24);
	return url->c_str();
}


void logGameInfo(const char*url,const char*type, void*doc) {
	using namespace rapidjson;
	Document*val = (Document*)doc;
	MemoryBuffer buffer;
	Writer<MemoryBuffer> writer(buffer);
	val->Accept(writer);
	char *s = new char[buffer.GetSize() + 1];
	s[buffer.GetSize()] = 0;
	memcpy(s, buffer.GetBuffer(), buffer.GetSize());
	action("logGameInfo", { userInfo->uid.c_str(), type, url, s });
	delete[]s;
}


HS(int, _ZN10NetManager21ParseDataFromResponseEPN7cocos2d7network12HttpResponseERN9rapidjson15GenericDocumentINS4_4UTF8IcEENS4_19MemoryPoolAllocatorINS4_12CrtAllocatorEEES9_EE, void*t, void*res, void*r)
HSUPER(true, _ZN10NetManager21ParseDataFromResponseEPN7cocos2d7network12HttpResponseERN9rapidjson15GenericDocumentINS4_4UTF8IcEENS4_19MemoryPoolAllocatorINS4_12CrtAllocatorEEES9_EE, t, res, r);
if (userInfo != nullptr) {
	const char*url = getRequestUrl(res);
	//LOGE("RESPONSE:%s", url);
	if (C_ZN10PveManager22onGetWarResultResponseEPN7cocos2d7network12HttpResponseE) {
		logGameInfo(url,"GetWarResult", r);
	} else if (C_ZN10PveManager18onDealNodeResponseEPN7cocos2d7network12HttpResponseE) {
		logGameInfo(url,"DealNode", r);
	}
	
	/*
	Document document;

	Document::AllocatorType& allocator = document.GetAllocator();
	Value contact(kArrayType);
	Value contact2(kArrayType);
	Value root(kArrayType);
	contact.PushBack("Lu//a\"", allocator).PushBack("Mio", allocator).PushBack("甲", allocator);
	contact2.PushBack("Lu// a", allocator).PushBack("Mio", allocator).PushBack("乙", allocator);
	root.PushBack(contact, allocator);
	root.PushBack(contact2, allocator);*/

	
	//LOGER("%d,%s", buffer.GetSize(), s);
}
return ret;
}