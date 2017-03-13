#include <sys/time.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int gettimeofday(struct timeval *tv, struct timezone *tz) {
	HAVOC(tv);
	HAVOC(tz);
	return klee_range(-1, 1, __FUNCTION__);
}
