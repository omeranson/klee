#include <time.h>

#include <klee/klee.h>

int clock_settime(clockid_t clk_id, const struct timespec *tp) {
	int retval = klee_int(__FUNCTION__);
	// TODO Set errno?
	klee_assume((retval == 0) || (retval == -1));
	return retval;
}
