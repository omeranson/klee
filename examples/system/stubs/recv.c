#include <alloca.h>
#include <string.h>
#include <sys/types.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
	HAVOC_SIZE(buf, len);
	ssize_t retval;
	klee_make_symbolic(&retval, sizeof(retval), __FUNCTION__);
	klee_assume(retval <= len);
	return retval;
}
