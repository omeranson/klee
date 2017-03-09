#include <sys/ioctl.h>

#include <klee/klee.h>

int ioctl(int fd, int request, ...) {
	int retval = klee_int(__FUNCTION__);
	// TODO Set errno?
	klee_assume((retval == 0) || (retval == -1));
	return retval;
}
