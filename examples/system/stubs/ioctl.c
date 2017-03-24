#include <errno.h>
#include <sys/ioctl.h>

#include <klee/klee.h>

int ioctl(int fd, int request, ...) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
