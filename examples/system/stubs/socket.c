#include <klee/klee.h>

int socket(int domain, int type, int protocol) {
	// TODO Set errno?
	return klee_range(-1, 1024, __FUNCTION__);
}
