#include <string.h>

#include <klee/klee.h>

int open(const char *filename, int flags, ...) {
	strlen(filename); // Verify path is readable till NUL terminator
	return klee_range(-1, 1024, __FUNCTION__);
}
