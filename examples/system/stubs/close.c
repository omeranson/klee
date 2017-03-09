#include <unistd.h>

#include <klee/klee.h>

int close(int fd) {
	int retval = klee_int(__FUNCTION__);
	// TODO Set errno?
	klee_assume((retval == 0) || (retval == -1));
	return retval;
}
