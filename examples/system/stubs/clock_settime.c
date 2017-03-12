#include <time.h>

#include <klee/klee.h>

int clock_settime(clockid_t clk_id, const struct timespec *tp) {
	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
