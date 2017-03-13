#include <string.h>

#include <klee/klee.h>

int chroot(const char *path) {
	strlen(path); // Verify path is readable till NUL terminator
	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
