#pragma once
#include <string>
class IO {
public:
	struct File{
		std::string entry;
		std::string path;
		bool exsit;
	};

	static File getFile(const char*name);
	static File getFile(const std::string&name) { return getFile(name.c_str()); }
};