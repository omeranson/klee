#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

pid_t waitpid(pid_t pid, int *status, int options) {
	if (status) {
		HAVOC(status);
	}
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 65536, __FUNCTION__);
}
