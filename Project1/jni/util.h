#pragma once
#include <string>

const char* format(const char*fmt, ...);
std::string readAllTextFromFile(const char*filename,bool trim = false);
void splitPath(const char*filename, char*path, char*name, char*ext);
char *strlwr(char *str);

int getShipInFleet(int fleetId, int index);
bool streq(const char*a, const char*b);
bool strew(const char*a, const char*b);
bool strsw(const char*a, const char*b);
std::string*createString(const char*str);
std::string*createString(const std::string&str);

bool encrypt(void*dest, const void*src, int*len,int maxLen);
bool decrypt(void*dest, const void*src, int*len, int maxLen);
int fsize(FILE*f);
int freadAll(void*buf, const char*filename);
void fwriteAll(void* buf, const char*filelname, int size);