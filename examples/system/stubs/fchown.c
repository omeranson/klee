#include <unistd.h>

#include <klee/klee.h>

int fchown(int fd, uid_t owner, gid_t group) {
	return klee_range(-1, 1, __FUNCTION__);
}
