#include <errno.h>

#include <klee/klee.h>

int shutdown(int fd, int how) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
