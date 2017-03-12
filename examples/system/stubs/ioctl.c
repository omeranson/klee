#include <sys/ioctl.h>

#include <klee/klee.h>

int ioctl(int fd, int request, ...) {
	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
