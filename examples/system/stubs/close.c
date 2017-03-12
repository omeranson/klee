#include <unistd.h>

#include <klee/klee.h>

int close(int fd) {
	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
