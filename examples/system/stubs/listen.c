
#include <klee/klee.h>

int listen(int fd, int backlog) {
	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
