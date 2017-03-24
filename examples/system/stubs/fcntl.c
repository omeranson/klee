#include <errno.h>

#include <klee/klee.h>

int fcntl(int fd, int cmd, ...) {
	// TODO Set errno?
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1024, __FUNCTION__);
}
