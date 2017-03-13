
#include <klee/klee.h>

int shutdown(int fd, int how) {
	return klee_range(-1, 1, __FUNCTION__);
}
