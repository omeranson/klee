#include <alloca.h>
#include <string.h>
#include <sys/time.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int gettimeofday(struct timeval *tv, void *tz) {
	if (tv) {
		HAVOC(tv);
	}
	if (tz) {
		HAVOC_SIZE(tz, sizeof(struct timezone));
	}
	return klee_range(-1, 1, __FUNCTION__);
}
