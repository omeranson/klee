
#include <klee/klee.h>

int getdtablesize(void) {
	return klee_range(0, 1026, __FUNCTION__);
}
