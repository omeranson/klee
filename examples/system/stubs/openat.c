#include <errno.h>
#include <string.h>

#include <klee/klee.h>

int openat(int dirfd, const char *filename, int flags, ...) {
	strlen(filename); // Verify path is readable till NUL terminator
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1024, __FUNCTION__);
}
