#include <errno.h>

#include <klee/klee.h>

int socket(int domain, int type, int protocol) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1024, __FUNCTION__);
}
