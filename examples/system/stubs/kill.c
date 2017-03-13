#include <sys/types.h>

#include <klee/klee.h>

int kill(pid_t pid, int sig) {
	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
