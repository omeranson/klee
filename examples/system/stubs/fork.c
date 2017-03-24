#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <klee/klee.h>

pid_t fork(void) {
	pid_t result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	errno = klee_int(__FUNCTION__);
	return result;
}
