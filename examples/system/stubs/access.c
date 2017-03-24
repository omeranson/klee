#include <errno.h>
#include <string.h>

#include <klee/klee.h>

int access(const char *pathname, int mode) {
	strlen(pathname);
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
