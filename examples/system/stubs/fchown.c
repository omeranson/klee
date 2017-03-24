#include <errno.h>
#include <unistd.h>

#include <klee/klee.h>

int fchown(int fd, uid_t owner, gid_t group) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
