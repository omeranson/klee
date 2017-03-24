#include <errno.h>

#include <klee/klee.h>

int nice(int inc) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-20, 20, __FUNCTION__);
}

