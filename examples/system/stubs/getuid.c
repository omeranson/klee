#include <sys/types.h>

#include <klee/klee.h>

uid_t getuid(void) {
	return klee_int(__FUNCTION__);
}

