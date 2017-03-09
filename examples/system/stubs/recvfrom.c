#include <alloca.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
		struct sockaddr *src_addr, socklen_t *addrlen) {
	HAVOC_SIZE(buf, len);
	if (src_addr) {
		HAVOC_SIZE(src_addr, *addrlen);
		*addrlen = klee_int(__FUNCTION__);
	}
	ssize_t retval;
	klee_make_symbolic(&retval, sizeof(retval), __FUNCTION__);
	klee_assume(retval <= len);
	return retval;
}
