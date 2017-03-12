#include <sys/types.h>

#include <klee/klee.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
	// TODO Set errno?
	return klee_range(-1, len+1, __FUNCTION__);
}
