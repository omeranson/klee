#include <errno.h>
#include <sys/types.h>

#include <klee/klee.h>

uid_t getuid(void) {
	errno = klee_int(__FUNCTION__);
	return klee_int(__FUNCTION__);
}

