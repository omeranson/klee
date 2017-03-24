#include <errno.h>
#include <sys/types.h>

#include <klee/klee.h>

int kill(pid_t pid, int sig) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
