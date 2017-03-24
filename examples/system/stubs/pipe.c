#include <errno.h>

#include <klee/klee.h>

int pipe(int pipefd[2]) {
	errno = klee_int(__FUNCTION__);
	pipefd[0] = klee_range(-1, 1025, __FUNCTION__);
	pipefd[1] = klee_range(-1, 1025, __FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
