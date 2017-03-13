#include <klee/klee.h>

int fcntl(int fd, int cmd, ...) {
	// TODO Set errno?
	return klee_range(-1, 1024, __FUNCTION__);
}
