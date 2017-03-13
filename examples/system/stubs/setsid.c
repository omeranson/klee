#include <unistd.h>

#include <klee/klee.h>

pid_t setsid(void) {
	return klee_range(-1, 1, __FUNCTION__);
}
