#include <sys/socket.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
	HAVOC_SIZE(addr, *addrlen);
	*addrlen = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
