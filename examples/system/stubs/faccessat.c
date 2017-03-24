#include <errno.h>
#include <string.h>

#include <klee/klee.h>

int faccessat(int dirfd, const char *pathname, int mode, int flags) {
	errno = klee_int(__FUNCTION__);
	strlen(pathname);
	return klee_range(-1, 1, __FUNCTION__);
}

