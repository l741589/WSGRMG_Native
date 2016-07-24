#include "IO.h"

IO::File IO::getFile(const char*name) {
	return{ name, name, true };
}

