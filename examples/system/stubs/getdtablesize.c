#include <errno.h>

#include <klee/klee.h>

int getdtablesize(void) {
	errno = klee_int(__FUNCTION__);
	return klee_range(0, 1026, __FUNCTION__);
}
