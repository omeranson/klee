#include <errno.h>
#include <sys/types.h>

#include <klee/klee.h>

int setgid(gid_t gid) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
