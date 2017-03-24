#include <errno.h>
#include <unistd.h>

#include <klee/klee.h>

int close(int fd) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
