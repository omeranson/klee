#include <errno.h>
#include <unistd.h>

#include <klee/klee.h>

pid_t setsid(void) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
