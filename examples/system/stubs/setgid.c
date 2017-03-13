#include <sys/types.h>

#include <klee/klee.h>

int setgid(gid_t gid) {
	return klee_range(-1, 1, __FUNCTION__);
}
