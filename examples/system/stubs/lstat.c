#include <alloca.h>
#include <string.h>
#include <sys/stat.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int lstat(const char *pathname, struct stat *buf) {
	strlen(pathname); // Verify path is readable till NUL terminator
	HAVOC(buf);
	return klee_range(-1, 1, __FUNCTION__);
}
