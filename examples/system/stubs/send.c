#include <sys/types.h>

#include <klee/klee.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
	int retval = klee_int(__FUNCTION__);
	// TODO Set errno?
	klee_assume((retval <= len) || (retval == -1));
	return retval;
}
