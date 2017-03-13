#include <sys/types.h>

#include <klee/klee.h>

pid_t getpid(void) {
	return klee_range(0, 65536, __FUNCTION__);
}

