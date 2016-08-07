#include "util.h"
#include "stdafx.h"
#include <io.h>
#include <string.h>
#include <ctype.h>
#include "ice/IceKey.h"

char __buffer[65536];
const char* format(const char*fmt, ...) {
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsnprintf(__buffer,65536, fmt, argptr);
	va_end(argptr);
	return __buffer;
}

#define IS_BLANK(s) ((s) == ' ' || (s) == '\t' || (s) == '\r' || (s) == '\n')

std::string readAllTextFromFile(const char*filename,bool trim) {
	if (!access(filename, R_OK)) return "";
	FILE*fp;
	fp = fopen(filename, "rb");// localfile文件名       
	fseek(fp, 0L, SEEK_END); /* 定位到文件末尾 */
	int flen = ftell(fp); /* 得到文件大小 */
	char *p = new char[flen + 1];
	if (p == NULL) {
		fclose(fp);
		return 0;
	}
	fseek(fp, 0L, SEEK_SET); /* 定位到文件开头 */
	fread(p, flen, 1, fp); /* 一次性读取全部文件内容 */
	p[flen] = 0; /* 字符串结束标志 */
	char *s = p;
	if (trim) {
		char*last = s + strlen(s) - 1;
		while (last >= s&&IS_BLANK(*last)) *last-- = 0;
		while (*s&&IS_BLANK(*s)) ++s;
	}
	std::string ret = s;
	delete[]p;
	return ret;
}


void splitPath(const char*filename,char*path, char*name, char*ext) {
	const char* lastDot = nullptr;
	const char* lastSlash = nullptr; 
	for (const char*p = filename; *p; ++p) {
		if (*p == '/') lastSlash = p;
		else if (*p == '.') lastDot = p;
	}
	if (lastDot < lastSlash) lastDot = nullptr;
	if (lastDot) strcpy(ext, lastDot + 1);
	if (lastSlash) {
		strncpy(path, filename, lastSlash - filename);
		if (lastDot) strncpy(name, lastSlash + 1, lastDot - lastSlash);
		else strcpy(name, lastSlash + 1);
	}
}

char *strlwr(char *str) {
	char *orign = str;
	for (; *str != '\0 '; str++)
		*str = tolower(*str);
	return orign;
}

int getShipInFleet(int fleetId, int index) {
	auto fi=UserManager::getInstance()->getIndexFleetInfo(fleetId);
	auto sptr = fi.shipStartPtr + index;
	if (sptr >= fi.shipEndPtr) return -1;
	auto ship = UserManager::getInstance()->getIndexUserShip(*sptr);
	if (ship == nullptr) return -1;
	return ship->cid;
}

bool streq(const char*a, const char*b) {
	return strcmp(a, b) == 0;
}

bool strew(const char*a, const char*b) {
	return  streq(a + strlen(a) - strlen(b), b);
}

bool strsw(const char*a, const char*b) {
	for (; *a&&*b; ++a, ++b) if (*a != *b) return false;
	return true;
}

typedef void (IceKey::*pf_converter)(const unsigned char *, unsigned char *) const;
void fixSize(int*size) {
	if (*size % 8 != 0) {
		*size = 8 * (*size / 8 + 1);
	}
}

bool convert(unsigned char*dest, const unsigned char*src, int*len,int maxLen,pf_converter converter) {
	fixSize(len);
	if (*len > maxLen) return false;
	IceKey ice(0);
	ice.set((unsigned char*)"W56RM6!N");
	for (auto i = 0; i < *len / 8; ++i)
		(ice.*converter)(src + 8 * i, dest + 8 * i);
	return true;
}

bool encrypt(void*dest, const void*src, int*len,int maxLen) {
	return convert((unsigned char*)dest, (unsigned char*)src, len, maxLen, &IceKey::encrypt);
}

bool decrypt(void*dest, const void*src, int*len, int maxLen) {
	return convert((unsigned char*)dest, (unsigned char*)src, len, maxLen, &IceKey::decrypt);
}


int fsize(FILE*f) {
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	return size;
}

int freadAll(void*buf, const char*filename) {
	FILE*f = fopen(filename, "rb");
	int size = fsize(f);
	fread(buf, size, 1, f);
	fclose(f);
	return size;
}

void fwriteAll(void* buf, const char*filelname, int size) {
	FILE*f = fopen(filelname, "wb");
	fwrite(filelname, size, 1, f);
	fclose(f);
}
