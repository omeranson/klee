#include <sys/types.h>
#include <sys/wait.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

pid_t waitpid(pid_t pid, int *status, int options) {
	if (status) {
		HAVOC(status);
	}
	return klee_range(-1, 65536, __FUNCTION__);
}
