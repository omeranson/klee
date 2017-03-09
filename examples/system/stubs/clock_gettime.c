#include <alloca.h>
#include <string.h>
#include <time.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
	HAVOC(tp);

	int retval = klee_int("clock_gettime");
	// TODO Set errno?
	klee_assume((retval == 0) || (retval == -1));
	return retval;
}
