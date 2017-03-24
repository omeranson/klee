#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int lstat(const char *pathname, struct stat *buf) {
	int len = strlen(pathname); // Verify path is readable till NUL terminator
	if (!len) {
		return -1;
	}
	HAVOC(buf);
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
