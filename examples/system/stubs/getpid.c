#include <errno.h>
#include <sys/types.h>

#include <klee/klee.h>

pid_t getpid(void) {
	errno = klee_int(__FUNCTION__);
	return klee_range(0, 65536, __FUNCTION__);
}

