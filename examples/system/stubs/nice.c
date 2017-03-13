#include <klee/klee.h>

int nice(int inc) {
	return klee_range(-20, 20, __FUNCTION__);
}

