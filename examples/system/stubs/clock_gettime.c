#include <alloca.h>
#include <string.h>
#include <time.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
	HAVOC(tp);

	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
