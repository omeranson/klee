#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
	HAVOC_SIZE(buf, len);
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, len+1, __FUNCTION__);
}
