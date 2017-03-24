#include <errno.h>

#include <klee/klee.h>

int listen(int fd, int backlog) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
