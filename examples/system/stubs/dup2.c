#include <errno.h>

#include <klee/klee.h>

int dup2(int oldfd, int newfd) {
	int retval = klee_int(__FUNCTION__);
	if ((retval != -1) && (retval != newfd)) {
		klee_silent_exit(0);
	}
	errno = klee_int(__FUNCTION__);
	return retval;
}
