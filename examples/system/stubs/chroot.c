#include <errno.h>
#include <string.h>

#include <klee/klee.h>

int chroot(const char *path) {
	strlen(path); // Verify path is readable till NUL terminator
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
